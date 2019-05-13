#pragma once

// openCV
#include <opencv2/core.hpp>

class MatrixViewer
{
public:
	MatrixViewer();

	static void showInformation(std::string_view label, const cv::Mat& matrix);

	static void showMatrix(std::string_view label, const cv::Mat& matrix);

	static void showFourier(std::string_view label, const cv::Mat& matrix, bool arrange = true);

	static void recenterDFT(cv::Mat& source);
};

