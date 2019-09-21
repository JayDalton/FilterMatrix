#include "pch.h"
#include "FileManager.h"

MatrixFileOpt FileManager::loadMatrixFileInfo(std::string_view filePath) const
{
   MatrixFileInfo file{ filePath };
   if (file.isValid())
   {
      return file;
   }
   return {};
}

void FileManager::appendMatrixFile(MatrixFileInfo matrixFile)
{
   m_fileList.push_back(matrixFile);
}

const MatrixFileList& FileManager::getFileList() const
{
   return m_fileList;
}

