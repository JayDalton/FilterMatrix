#include "precompheader.h"

#include "ImageMatrix.h"

struct ImageMatrix::Impl
{

};

ImageMatrix::ImageMatrix(cv::Mat matrix)
   : m(std::make_unique<Impl>())
{

}

ImageMatrix::~ImageMatrix() = default;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
