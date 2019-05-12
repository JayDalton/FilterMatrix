#include "pch.h"
#include "MatrixViewer.h"


MatrixViewer::MatrixViewer()
{
}

void MatrixViewer::showMatrix(std::string_view label, cv::Mat matrix)
{
	cv::Mat visible;
	cv::Size size(matrix.cols, matrix.rows);
	cv::resize(matrix, visible, size / 10);
	cv::normalize(visible, visible, 0, 255, cv::NORM_MINMAX);
	visible.convertTo(visible, CV_8U);
	cv::imshow(label.data(), visible);
	//cv::waitKey();
}
