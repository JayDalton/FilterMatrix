#include "pch.h"
#include "MatrixManager.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

void MatrixManager::loadMatrixFromFile(MatrixFileInfo fileInfo)
{
   if (!fileInfo.isValid())
   {
      return;
   }

   m_fileInfo = fileInfo;

   m_source = importMatrixFile(fileInfo);

   m_floating = transformToFloating(m_source);

   m_fourier = transformToFourier(m_floating);

   m_magnitude = transformToMagnitude(m_fourier);

   m_target = transformToInteger(m_fourier);
}

cv::Mat MatrixManager::getSourceData() const
{
   return m_magnitude;
}

cv::Mat MatrixManager::importMatrixFile(MatrixFileInfo info) const
{
   return cv::imread(info.getPath().string(), cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);
}

cv::Mat MatrixManager::transformToFloating(cv::Mat source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_32F, 1.0 / USHRT_MAX);
   return converted;
}

cv::Mat MatrixManager::transformToInteger(cv::Mat source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_16UC1, USHRT_MAX);
   return converted;
}

cv::Mat MatrixManager::transformToFourier(cv::Mat source) const
{
   assert(source.depth() == CV_32F);		// 32 bit
   assert(source.channels() == 1);			// 1 chan

   MethodTimer timer{__func__};
   auto now{ cv::getTickCount() };

   cv::Mat padded;
   cv::copyMakeBorder(source, padded, 
      0, cv::getOptimalDFTSize(source.rows) - source.rows,
      0, cv::getOptimalDFTSize(source.cols) - source.cols,
      cv::BORDER_CONSTANT, cv::Scalar::all(0)
   );

   cv::Mat result;
   cv::dft(padded, result, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);

   dump_duration(now, "complete transform");
   return result;
}

cv::Mat MatrixManager::transformToMagnitude(cv::Mat source) const
{
   assert(source.depth() == CV_32F);		// 32 bit
   assert(source.channels() == 2);			// 2 chan

   auto now{ cv::getTickCount() };

   cv::Mat planes[2];
   cv::split(source, planes);

   cv::magnitude(
      planes[0], 
      planes[1], 
      planes[0]
   );

   cv::Mat result = planes[0];
   result += cv::Scalar::all(1);							// switch to logarithmic scale
   cv::log(result, result);

   dump_duration(now, "complete magnitude");
   std::cout << result.channels() << std::endl;
   std::cout << result.type() << std::endl;

   return result;
}

cv::Mat MatrixManager::transformToInvert(cv::Mat source) const
{
   assert(source.depth() == CV_32F);		// 32 bit
   assert(source.channels() == 2);			// 2 chan

   auto now{ cv::getTickCount() };

   cv::Mat target;
   cv::dft(source, target, 
      cv::DFT_COMPLEX_INPUT | cv::DFT_REAL_OUTPUT | 
      cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_ROWS
   );

   dump_duration(now, "complete dft invert: ");
   return target;
}

int64 MatrixManager::dump_duration(int64 now, std::string label) const
{
   auto duration = cv::getTickCount() - now;
   std::cout << label << ": " << duration / cv::getTickFrequency() << std::endl;
   return cv::getTickCount();
}
