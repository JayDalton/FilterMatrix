#include <pch.h>

#include "DataLayer/DataLayer.h"
#include "MatrixFile.h"

namespace fs = std::filesystem;

DataLayer::DataLayer()
{
}

void DataLayer::loadConfiguration()
{
}

MatrixFileOpt DataLayer::openMatrixFile(std::string_view importFileName)
{
   if (auto fileOpt = m_fileManger.loadMatrixFileInfo(importFileName))
   {
      m_fileManger.appendMatrixFile(fileOpt.value());
      return fileOpt;
   }
   return {};
}

void DataLayer::loadMatrixFile(MatrixFileInfo file)
{
   m_matrixManger.loadMatrixFromFile(file);
}
