#include "pch.h"

// std
#include <iostream>
#include <string_view>
#include <filesystem>

// openCV
#include <opencv2/core.hpp>

//using namespace std;
//using namespace winrt;
//using namespace Windows::Foundation;

#include "MatrixFilter.h"
#include "MatrixViewer.h"

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

	MatrixViewer::showMatrix("Vorschau Original", matrix);

	cv::Mat floatImage;
	matrix.convertTo(floatImage, CV_32F, 1.0 / USHRT_MAX);

	MatrixViewer::showMatrix("Vorschau Floating", floatImage);

	auto fourierMTX{ MatrixFilter::linewiseTransform(floatImage) };
	//MatrixFilter::writeMatrixToFile(floatImage, "imp.floating.xml");
	
	auto transformMTX{ MatrixFilter::completeTransform(floatImage) };
	//MatrixFilter::writeMatrixToFile(floatImage, "imp.complete.xml");

	auto formatedMagnitudeMTX{ MatrixFilter::formatMagnitude(fourierMTX) };
	MatrixFilter::writeMatrixToFile(formatedMagnitudeMTX, "imp.formatedMagnitude.xml");

	auto completeMagnitudeMTX{ MatrixFilter::completeMagnitude(transformMTX) };
	MatrixFilter::writeMatrixToFile(completeMagnitudeMTX, "imp.completeMagnitude.xml");

	cv::waitKey();
}
