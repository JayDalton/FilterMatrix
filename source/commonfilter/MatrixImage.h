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
   std::string to_string() const;
};

struct MatrixRange
{
   MatrixPoint x{};
   MatrixPoint y{};
};

using PropertyLabel = std::string;
using PropertyValue = std::variant<
   signed, unsigned, float, double, MatrixPoint
>;

struct MatrixProperty
{
   PropertyLabel m_label;
   PropertyValue m_value;
};

using MatrixPropertyList = std::vector<MatrixProperty>;

//////////////////////////////////////////////////////////////////////////////////

struct MatrixImage
{
   explicit MatrixImage(MatrixFileInfo info);
   ~MatrixImage();

   MatrixPropertyList getMatrixInfo();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
