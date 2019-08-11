#include "pch.h"

#include "MatrixViewer.h"

#include <iostream>

// openCV
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

MatrixViewer::MatrixViewer()
{
}

void MatrixViewer::showInformation(std::string_view label, const cv::Mat& matrix)
{
	MethodTimer timer{ __func__ };

	double min_val{ 0 }, max_val{ 0 };
	cv::Point min_loc{ 0,0 }, max_loc{ 0,0 };
	cv::minMaxLoc(matrix, &min_val, &max_val, &min_loc, &max_loc);

	std::cout << label << std::endl;
	std::cout << "type: " << matrix.type() << " " << "channels: " << matrix.channels() << std::endl;
	std::cout << "rows: " << matrix.rows << " " << "cols: " << matrix.cols << std::endl;
	std::cout << "minVal: " << min_val << " " << "maxVal: " << max_val << std::endl;
	std::cout << "minLoc: " << min_loc << " " << "maxLoc: " << max_loc << std::endl;
}

void MatrixViewer::showMatrix(std::string_view label, const cv::Mat& matrix)
{
	MethodTimer timer{ __func__ };

	cv::Mat visible;
	cv::Size size(matrix.cols, matrix.rows);
	cv::resize(matrix, visible, size / 10);
	cv::normalize(visible, visible, 0, 255, cv::NORM_MINMAX);
	visible.convertTo(visible, CV_8U);
	cv::imshow(label.data(), visible);
	//cv::waitKey();
}

void MatrixViewer::showFourier(std::string_view label, const cv::Mat& matrix, bool arrange)
{
	cv::Mat splitArray[2] { 
		cv::Mat::zeros(matrix.size(), CV_32F), 
		cv::Mat::zeros(matrix.size(), CV_32F) 
	};
	cv::split(matrix, splitArray);

	cv::Mat magnitudeDFT;
	cv::magnitude(splitArray[0], splitArray[1], magnitudeDFT);

	magnitudeDFT += cv::Scalar::all(1);
	cv::log(magnitudeDFT, magnitudeDFT);

	// crop the spectrum, if it has an odd number of rows or columns
	magnitudeDFT = magnitudeDFT(cv::Rect(0, 0, magnitudeDFT.cols & -2, magnitudeDFT.rows & -2));

	if (arrange) { recenterDFT(magnitudeDFT); }

	cv::normalize(magnitudeDFT, magnitudeDFT, 0, 1, cv::NORM_MINMAX);

	showMatrix(label, magnitudeDFT);
}

void MatrixViewer::recenterDFT(cv::Mat& source)
{
	int centerX = source.cols / 2;
	int centerY = source.rows / 2;

	cv::Mat q1(source, cv::Rect(0, 0, centerX, centerY));
	cv::Mat q2(source, cv::Rect(centerX, 0, centerX, centerY));
	cv::Mat q3(source, cv::Rect(0, centerY, centerX, centerY));
	cv::Mat q4(source, cv::Rect(centerX, centerY, centerX, centerY));

	cv::Mat swapMap;

	q1.copyTo(swapMap);
	q4.copyTo(q1);
	swapMap.copyTo(q4);

	q2.copyTo(swapMap);
	q3.copyTo(q2);
	swapMap.copyTo(q3);
}
