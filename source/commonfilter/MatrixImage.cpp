#include "pch.h"

#include "MatrixImage.h"


struct MatrixImage::Impl
{
   explicit Impl(MatrixFileInfo info) : m_fileInfo(info) {}

   //cv::Mat m_source;    // ImageMatrix
   //cv::Mat m_floating;
   //cv::Mat m_fourier;
   //cv::Mat m_magnitude;
   //cv::Mat m_target;
   MatrixFileInfo m_fileInfo;
   MatrixPropertyList m_imageinfo;
};

MatrixImage::MatrixImage(MatrixFileInfo info)
   : m(std::make_unique<Impl>(info))
{
}

MatrixImage::~MatrixImage() = default;
