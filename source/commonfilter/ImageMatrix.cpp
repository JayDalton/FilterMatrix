#include "pch.h"
#include "ImageMatrix.h"

struct ImageMatrix::Impl
{

};

ImageMatrix::ImageMatrix(cv::Mat matrix)
   : m(std::make_unique<Impl>())
{

}

ImageMatrix::~ImageMatrix() = default;
