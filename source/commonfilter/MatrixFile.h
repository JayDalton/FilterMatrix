#pragma once

#include <filesystem>

namespace fs = std::filesystem;

struct MatrixFile
{
   explicit MatrixFile(std::string_view filePath);



private:
   fs::path m_path;
};

