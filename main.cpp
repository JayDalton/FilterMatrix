#include "pch.h"

// std
#include <iostream>
#include <filesystem>
#include <string_view>

// openCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// own
#include "MatrixFilter.h"
#include "MatrixViewer.h"

namespace fs = std::filesystem;

int main()
{
	winrt::init_apartment();

	const cv::String keys =
		"{help h usage ? |          | print this message   }"
		"{@image1        |          | image1 for compare   }"
		"{@image2        |result.pgm| image2 for compare   }"
	;

	cv::CommandLineParser parser(__argc, __argv, keys);
	parser.about("Grid Artifacts Elimination in Computed Radiographic Images v0.0.1");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	auto importFileName{ parser.get<std::string>(0) };
	auto exportFileName{ parser.get<std::string>(1) };

	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

	auto path{ fs::path(importFileName) };
	if (!fs::exists(path))
	{
		std::cout << " file does not exist: " << path << std::endl;
		return -1;
	}

	if (!path.has_extension() || path.extension() != ".pgm")
	{
		std::cout << " wrong file extension. Only PGM support." << std::endl;
		return -1;
	}

	auto matrix{ MatrixFilter::loadFileMatrix(path) };
	if (matrix.empty())
	{
		std::cout << " matrix is empty" << std::endl;
		return -1;
	}

	//MatrixFilter::writeMatrixToFile(matrix, "imp.original.xml");
	MatrixViewer::showMatrix("Vorschau Original", matrix);
	MatrixViewer::showInformation("Infos original", matrix);

	auto floatingMTX{ MatrixFilter::convertToFloat(matrix) };
	//MatrixFilter::writeMatrixToFile(floatingMTX, "imp.floating.xml");
	MatrixViewer::showMatrix("Vorschau Floating", floatingMTX);
	MatrixViewer::showInformation("Infos Floating", floatingMTX);

	auto linewiseMTX{ MatrixFilter::linewiseTransform(floatingMTX) };
	//MatrixFilter::writeMatrixToFile(linewiseMTX, "imp.linewise.xml");
	MatrixViewer::showFourier("Fourier View old true", linewiseMTX);

	auto transformMTX{ MatrixFilter::completeTransform(floatingMTX) };
	//MatrixFilter::writeMatrixToFile(transformMTX, "imp.transform.xml");
	MatrixViewer::showFourier("Fourier View new true", transformMTX);

	auto linewiseInvert{ MatrixFilter::linewiseInvertDFT(linewiseMTX) };
	MatrixViewer::showMatrix("Invert linewise", linewiseInvert);

	auto transformInvert{ MatrixFilter::completeInvertDFT(transformMTX) };
	MatrixViewer::showMatrix("Invert complete", transformInvert);

	auto resultMatrix{MatrixFilter::convertToReal(linewiseInvert)};
	MatrixFilter::saveFileMatrix(path.replace_filename("result.pgm"), resultMatrix);

	//cv::Mat resultImage;
	//linewiseInvert.convertTo(resultImage, CV_16UC1, USHRT_MAX);
	//cv::imwrite(path.replace_filename("result.pgm").string(), resultImage);

	cv::waitKey();
}
