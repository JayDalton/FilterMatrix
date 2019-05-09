#include "pch.h"

#include <iostream>
#include <string_view>
#include <filesystem>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace winrt;
using namespace Windows::Foundation;

int main()
{
	winrt::init_apartment();

	const cv::String keys =
		"{help h usage ? |      | print this message   }"
		"{@image1        |      | image1 for compare   }"
		"{@image2        |<none>| image2 for compare   }"
	;

	cv::CommandLineParser parser(__argc, __argv, keys);
	parser.about("Grid Artifacts Elimination in Computed Radiographic Images v0.0.1");
	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	auto importFileName{ parser.get<cv::String>(0) };
	auto exportFileName{ parser.get<cv::String>(1) };

	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

	auto path{ std::string(importFileName) };
	if (!std::filesystem::exists(path))
	{
		std::cout << " file does not exist: " << path << std::endl;
		return -1;
	}

	auto matrix{ cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE | CV_LOAD_IMAGE_ANYDEPTH) };
	if (matrix.empty())
	{
		std::cout << " matrix is empty" << std::endl;
		return -1;
	}

	double min_val{ 0 }, max_val{ 0 };
	cv::Point min_loc{ 0,0 }, max_loc{ 0,0 };
	cv::minMaxLoc(matrix, &min_val, &max_val, &min_loc, &max_loc);
	std::cout << "rows: " << matrix.rows << " " << "cols: " << matrix.cols << std::endl;
	std::cout << "minVal: " << min_val << " " << "maxVal: " << max_val << std::endl;
	std::cout << "minLoc: " << min_loc << " " << "maxLoc: " << max_loc << std::endl;

	cv::Mat visible;
	cv::Size size(matrix.cols, matrix.rows);
	cv::resize(matrix, visible, size / 10);
	cv::normalize(visible, visible, 0, 255, cv::NORM_MINMAX);
	visible.convertTo(visible, CV_8U);
	cv::imshow("Vorschau", visible);
	cv::waitKey();

	cv::Mat floatImage;
	matrix.convertTo(floatImage, CV_32F, 1.0 / USHRT_MAX);
	assert(matrix.depth() == CV_32F);		// 32 bit
	assert(matrix.channels() == 1);			// 1 chan

	cv::Mat dftImage;

}
