#include "pch.h"

// std
#include <iostream>
#include <string_view>

// openCV
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "MatrixFilter.h"

struct MatrixFilter::Impl
{
	int64 dump_duration(int64 now, std::string label);
};

int64 MatrixFilter::Impl::dump_duration(int64 now, std::string label)
{
	auto duration = cv::getTickCount() - now;
	std::cout << label << ": " << duration / cv::getTickFrequency() << std::endl;
	return cv::getTickCount();
}

MatrixFilter::MatrixFilter()
{
}

MatrixFilter::~MatrixFilter() = default;

int64 MatrixFilter::dump_duration(int64 now, std::string label)
{
	auto duration = cv::getTickCount() - now;
	std::cout << label << ": " << duration / cv::getTickFrequency() << std::endl;
	return cv::getTickCount();
}

cv::Mat MatrixFilter::linewiseTransform(const cv::Mat& source)
{
	assert(source.depth() == CV_32F);		// 32 bit
	assert(source.channels() == 1);			// 1 chan

	cv::Mat result{};
	auto now{ cv::getTickCount() };

	for (int row = 0; row < source.rows; ++row)
	{
		cv::Mat one_row = source.row(row);

		cv::Mat paddedLine;								// expand input image to optimal size
		int m = cv::getOptimalDFTSize(one_row.rows);
		int n = cv::getOptimalDFTSize(one_row.cols);		// on the border add zero values
		cv::copyMakeBorder(one_row, paddedLine, 0, m - one_row.rows, 0, n - one_row.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		cv::Mat linePlanes[] = { cv::Mat_<float>(paddedLine), cv::Mat::zeros(paddedLine.size(), CV_32F) };

		cv::Mat complexLine;
		cv::merge(linePlanes, 2, complexLine);					// Add to the expanded another plane with zeros

		cv::dft(complexLine, complexLine, cv::DFT_COMPLEX_OUTPUT);	// this way the result may fit in the source matrix

		result.push_back(complexLine);
	}

	dump_duration(now, "linewise transform");
	std::cout << result.channels() << std::endl;
	std::cout << result.type() << std::endl;

	return result;
}

cv::Mat MatrixFilter::completeTransform(const cv::Mat& source)
{
	assert(source.depth() == CV_32F);		// 32 bit
	assert(source.channels() == 1);			// 1 chan

	auto now{ cv::getTickCount() };

	cv::Mat padded;								// expand input image to optimal size
	int m = cv::getOptimalDFTSize(source.rows);
	int n = cv::getOptimalDFTSize(source.cols);		// on the border add zero values
	cv::copyMakeBorder(
		source, padded, 
		0, m - source.rows, 
		0, n - source.cols, 
		cv::BORDER_CONSTANT, 
		cv::Scalar::all(0)
	);

	cv::Mat result;
	cv::dft(
		padded, result, 
		cv::DFT_ROWS + cv::DFT_SCALE 
		+ cv::DFT_COMPLEX_OUTPUT
	);

	dump_duration(now, "complete magnitude");
	std::cout << result.channels() << std::endl;
	std::cout << result.type() << std::endl;

	return result;
}

cv::Mat MatrixFilter::formatMagnitude(const cv::Mat& source)
{
	assert(source.depth() == CV_32F);		// 32 bit
	assert(source.channels() == 2);			// 2 chan

	cv::Mat result;
	auto now{ cv::getTickCount() };

	for (int row = 0; row < source.rows; ++row)
	{
		cv::Mat dft_row = source.row(row);

		cv::Mat planes[2];
		cv::split(dft_row, planes);						// planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

		cv::Mat magI;									// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
		cv::magnitude(planes[0], planes[1], magI);		// planes[0] = magnitude
		magI += cv::Scalar::all(1);							// switch to logarithmic scale
		cv::log(magI, magI);
		result.push_back(magI);
	}

	dump_duration(now, "formated magnitude");
	std::cout << result.channels() << std::endl;
	std::cout << result.type() << std::endl;

	return result;
}

cv::Mat MatrixFilter::completeMagnitude(const cv::Mat& source)
{
	assert(source.depth() == CV_32F);		// 32 bit
	assert(source.channels() == 2);			// 2 chan

	auto now{ cv::getTickCount() };

	cv::Mat result;
	cv::magnitude(
		source.ptr<double>(0)[0], 
		source.ptr<double>(1)[0], 
		result
	);
	result += cv::Scalar::all(1);							// switch to logarithmic scale
	cv::log(result, result);

	dump_duration(now, "complete to magnitude");
	std::cout << result.channels() << std::endl;
	std::cout << result.type() << std::endl;

	return result;
}

void MatrixFilter::writeMatrixToFile(const cv::Mat& matrix, std::string_view filename)
{
	auto now { cv::getTickCount() };
	cv::FileStorage file { filename.data(), cv::FileStorage::WRITE };
	file << "OpenCvMatrix" << matrix;
	dump_duration(now, "matrix written to file");
}

