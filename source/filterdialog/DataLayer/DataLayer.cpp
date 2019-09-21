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

bool DataLayer::readMatrixFileInfo(const StringVector& pathList)
{
   return m_fileManger.loadMatrixFileInfo(pathList);
}

bool DataLayer::readMatrixFileInfo(std::string_view importFileName)
{
   return m_fileManger.loadMatrixFileInfo(importFileName);
}

void DataLayer::loadMatrixFile(MatrixFileInfo file)
{
   m_matrixManger.loadMatrixFromFile(file);
}

cv::Mat DataLayer::currentMatrix()
{
   return m_matrixManger.getSourceData();
}

const MatrixFileRepository& DataLayer::getFileRepository() const
{
   return m_fileManger.getFileList();
}
