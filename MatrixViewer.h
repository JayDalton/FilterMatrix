#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class MatrixViewer
{
public:
	MatrixViewer();

	static void showMatrix(std::string_view label, const cv::Mat& matrix);

	static void showFourier(std::string_view label, const cv::Mat& matrix, bool arrange = true);

	static void recenterDFT(cv::Mat& source);
};

