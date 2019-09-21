#include "pch.h"

#include "MatrixFile.h"

MatrixFile::MatrixFile(std::string_view filePath)
   : m_path(filePath)
{
}

bool MatrixFile::isValid() const
{
   return fs::exists(m_path) 
      && fs::is_regular_file(m_path)
      && m_path.has_extension()
      && std::any_of(m_validExtensions.cbegin(), m_validExtensions.cend(), 
         [ext = m_path.extension().string()](const std::string& input) { return input == ext; }
      )
   ;
}

MatrixFile::Type MatrixFile::getFileType() const
{
   return Type::Graymap;
}

unsigned MatrixFile::getFileSize() const
{
   return fs::file_size(m_path);
}

std::string MatrixFile::getFileName() const
{
   return m_path.filename().string();
}

std::string MatrixFile::getFilePath() const
{
   return m_path.root_directory().string();
}

std::string MatrixFile::getExtension() const
{
   return m_path.extension().string();
}
