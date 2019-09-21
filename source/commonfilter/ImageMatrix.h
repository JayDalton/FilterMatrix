#pragma once

#include <opencv2/core.hpp>

struct ImageMatrix
{
   explicit ImageMatrix(cv::Mat matrix);
   ~ImageMatrix();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

using ImageMatrixUPtr = std::unique_ptr<ImageMatrix>;
