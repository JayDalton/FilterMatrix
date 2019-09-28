#include "precompheader.h"

#include "FileManager.h"

bool FileManager::loadMatrixFileInfo(std::string_view filePath)
{
   MatrixFileInfo file{ filePath };
   if (file.isValid())
   {
      m_fileList.push_back(file);
      return true;
   }
   return false;
}

bool FileManager::loadMatrixFileInfo(const StringVector& fileList)
{
   std::vector<bool> res;
   for (const auto& info : fileList)
   {
      spdlog::debug("load file info: {0}", info);
      res.push_back(loadMatrixFileInfo(info));
   }
   return std::all_of(res.cbegin(), res.cend(), [](bool res) { return res; });
}

void FileManager::appendMatrixFile(MatrixFileInfo matrixFile)
{
   m_fileList.push_back(matrixFile);
}

void FileManager::appendMatrixFileList(MatrixFileList fileList)
{
   m_fileList.assign(fileList.cbegin(), fileList.cend());
}

const MatrixFileList& FileManager::getFileList() const
{
   return m_fileList;
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
