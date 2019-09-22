#pragma once

#include <vector>
#include <string>
#include <variant>
#include <memory>

#include "MatrixFile.h"

struct MatrixPropertyPoint
{
   // cv::Point
   signed x{ 0 };
   signed y{ 0 };
};

using MatrixPropertyValue = std::variant<unsigned, float, double>;

struct MatrixProperty
{
   std::string m_label;
   MatrixPropertyValue m_value;
};
using MatrixPropertyList = std::vector<MatrixProperty>;

//struct MatrixImageInfo
//{
//   std::vector<MatrixProperty> m_property;
//};
//////////////////////////////////////////////////////////////////////////////////

struct MatrixImage
{
   MatrixImage(MatrixFileInfo info);
   ~MatrixImage();

   MatrixPropertyList getMatrixInfo();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

