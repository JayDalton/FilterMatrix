#pragma once

#include <opencv2/core/mat.hpp>

#include "ImageMatrix.h"

#include "MatrixFile.h"
#include "MatrixImage.h"

enum class MatrixLayer { Source, Floating, Fourier, Magnitude, Target, Count };

struct MatrixManager
{

   void loadMatrixFromFile(MatrixFileInfo fileInfo);

   cv::Mat getSourceData(MatrixLayer layer) const;

   MatrixPropertyList getMatrixPropertyList(MatrixLayer layer) const;

private:
   cv::Mat importMatrixFile(MatrixFileInfo info) const;
   cv::Mat transformToFloating(const cv::Mat& source) const;
   cv::Mat transformToInteger(const cv::Mat& source) const;
   cv::Mat transformToFourier(const cv::Mat& source) const;
   cv::Mat transformToMagnitude(const cv::Mat& source) const;
   cv::Mat transformToInvert(const cv::Mat& source) const;

   int64 dump_duration(int64 now, std::string label) const;

   MatrixPropertyList showInformation(const cv::Mat& matrix) const;

private:

   // MatrixImage
   //MatrixImage m_matrix;

   MatrixFileInfo m_fileInfo{""};
   cv::Mat m_source;    // ImageMatrix
   cv::Mat m_floating;
   cv::Mat m_fourier;
   cv::Mat m_magnitude;
   cv::Mat m_target;

   // MatrixImage
   //ImageMatrixUPtr m_source{ nullptr };
   //ImageMatrixUPtr m_original{ nullptr };
   //ImageMatrixUPtr m_floating{ nullptr };
   //ImageMatrixUPtr m_fourier{ nullptr };
   //ImageMatrixUPtr m_magnitude{ nullptr };
   //ImageMatrixUPtr m_target{ nullptr };

   // future ...
   //std::vector<MatrixImage> m_matrices;
};

