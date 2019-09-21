#include "pch.h"
#include "FileManager.h"

MatrixFileOpt FileManager::findMatrixFile(std::string_view filePath) const
{
   MatrixFile file{ filePath };
   if (file.isValid())
   {
      return file;
   }
   return {};
}

void FileManager::appendMatrixFile(MatrixFile matrixFile)
{
   m_fileList.push_back(matrixFile);
}

const MatrixFileList& FileManager::getFileList() const
{
   return m_fileList;
}

