#pragma once

#include <filesystem>

namespace fs = std::filesystem;

struct MatrixFile
{
   enum class Type { None, Graymap, Count };

   explicit MatrixFile(std::string_view filePath);

   void tes(fs::path p)
   {
      auto size = fs::file_size(p);
   }

   Type m_fileType;
   unsigned m_fileSize;
   std::string m_fileName;
   std::string m_filePath;
   std::string m_extension;

private:
   fs::path m_pathInfo;
};

