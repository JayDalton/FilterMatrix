#pragma once

#include <opencv2/core.hpp>

class MatrixFilter
{
public:
	~MatrixFilter();
	MatrixFilter();

	static cv::Mat linewiseTransform(const cv::Mat& source);
	static cv::Mat formatMagnitude(const cv::Mat& source);
	static void writeMatrixToFile(const cv::Mat& matrix, std::string_view filename);

private:
	struct Impl;
	std::unique_ptr<Impl> m;

	static int64 dump_duration(int64 now, std::string label);

};

