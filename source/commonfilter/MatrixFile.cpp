#include "precompheader.h"

#include "MatrixFile.h"

MatrixFileInfo::MatrixFileInfo(std::string_view filePath)
   : m_path(filePath)
{
}

const fs::path& MatrixFileInfo::getPath() const
{
   return m_path;
}

bool MatrixFileInfo::isValid() const
{
   return fs::exists(m_path) 
      && fs::is_regular_file(m_path)
      && m_path.has_extension()
      && std::any_of(m_validExtensions.cbegin(), m_validExtensions.cend(), 
         [ext = m_path.extension().string()](const std::string& input) { return input == ext; }
      )
   ;
}

MatrixFileInfo::Type MatrixFileInfo::getFileType() const
{
   return Type::Graymap;
}

unsigned MatrixFileInfo::getFileSize() const
{
   return fs::file_size(m_path);
}

std::string MatrixFileInfo::getFileName() const
{
   return m_path.filename().string();
}

std::string MatrixFileInfo::getFilePath() const
{
   return m_path.root_directory().string();
}

std::string MatrixFileInfo::getExtension() const
{
   return m_path.extension().string();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
