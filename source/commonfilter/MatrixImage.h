#pragma once

#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <complex>

#include "MatrixFile.h"

struct MatrixPoint
{
   signed x{ 0 };
   signed y{ 0 };
};

struct MatrixRange
{
   MatrixPoint x{};
   MatrixPoint y{};
};

using MatrixPropertyValue = std::variant<
   signed, unsigned, float, double, MatrixPoint
>;

struct MatrixProperty
{
   std::string m_label;
   MatrixPropertyValue m_value;
};

using MatrixPropertyList = std::vector<MatrixProperty>;

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

