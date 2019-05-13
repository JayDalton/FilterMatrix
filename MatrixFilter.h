#pragma once

// std
#include <filesystem>

// openCV
#include <opencv2/core.hpp>

namespace fs = std::filesystem;

class MatrixFilter
{
public:
	~MatrixFilter();
	MatrixFilter();

	static cv::Mat loadFileMatrix(const fs::path& path);
	static cv::Mat convertToFloat(const cv::Mat& source);

	static cv::Mat convertToReal(const cv::Mat& source);
	static void saveFileMatrix(fs::path path, const cv::Mat& source);

	static cv::Mat linewiseTransform(const cv::Mat& source);
	static cv::Mat completeTransform(const cv::Mat& source);

	static cv::Mat formatMagnitude(const cv::Mat& source);
	static cv::Mat completeMagnitude(const cv::Mat& source);

	static cv::Mat linewiseInvertDFT(const cv::Mat& source);
	static cv::Mat completeInvertDFT(const cv::Mat& source);

	static void writeMatrixToFile(const cv::Mat& matrix, std::string_view filename);

private:
	struct Impl;
	std::unique_ptr<Impl> m;

	static int64 dump_duration(int64 now, std::string label);

};

