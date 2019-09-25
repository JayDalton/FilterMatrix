#include "precompheader.h"

#include "MatrixManager.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "MatrixImage.h"

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

cv::Mat MatrixManager::getSourceData(MatrixLayer layer) const
{
   switch (layer)
   {
   case MatrixLayer::Source:
      return m_source;
   case MatrixLayer::Floating:
      return m_floating;
   case MatrixLayer::Fourier:
      return m_fourier;
   case MatrixLayer::Magnitude:
      return m_magnitude;
   case MatrixLayer::Target:
      return m_target;
   default:
      return {};
   }
}

MatrixPropertyList MatrixManager::getMatrixPropertyList(MatrixLayer layer) const
{
   switch (layer)
   {
   case MatrixLayer::Source:
      return showInformation(m_source);
   case MatrixLayer::Floating:
      return showInformation(m_floating);
   case MatrixLayer::Fourier:
      return showInformation(m_fourier);
   case MatrixLayer::Magnitude:
      return showInformation(m_magnitude);
   case MatrixLayer::Target:
      return showInformation(m_target);
   default:
      return {};
   }
}

cv::Mat MatrixManager::importMatrixFile(MatrixFileInfo info) const
{
   return cv::imread(info.getPath().string(), cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);
}

cv::Mat MatrixManager::transformToFloating(const cv::Mat& source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_32F, 1.0 / USHRT_MAX); // float
   return converted;
}

cv::Mat MatrixManager::transformToInteger(const cv::Mat& source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_16UC1, USHRT_MAX);  // short
   return converted;
}

cv::Mat MatrixManager::transformToFourier(const cv::Mat& source) const
{
   assert(source.depth() == CV_32F);		// 32 bit - float
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
   assert(result.depth() == CV_32F);		// 32 bit - float
   assert(result.channels() == 2);			// 2 chan

   return result;
}

cv::Mat MatrixManager::transformToMagnitude(const cv::Mat& source) const
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
   assert(result.depth() == CV_32F);		// 32 bit - float
   assert(result.channels() == 1);			// 1 chan

   return result;
}

cv::Mat MatrixManager::transformToInvert(const cv::Mat& source) const
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

MatrixPropertyList MatrixManager::showInformation(const cv::Mat& matrix) const
{
   MethodTimer timer{ __func__ };

   double min_val{ 0 }, max_val{ 0 };
   cv::Point min_loc{ 0,0 }, max_loc{ 0,0 };
   cv::minMaxLoc(matrix, &min_val, &max_val, &min_loc, &max_loc);

   return MatrixPropertyList {
      MatrixProperty{"Type", matrix.type()},
      MatrixProperty{"Rows", matrix.rows},
      MatrixProperty{"Columns", matrix.cols},
      MatrixProperty{"Channels", matrix.channels()},
      MatrixProperty{"Minimum", min_val},
      MatrixProperty{"Maximum", max_val},
      MatrixProperty{"Min Loc", MatrixPoint{min_loc.x, min_loc.y}},
      MatrixProperty{"Max Loc", MatrixPoint{max_loc.x, max_loc.y}},
   };
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
