#include <precompheader.h>

#include "DataLayer/DataLayer.h"
#include "MatrixFile.h"

namespace fs = std::filesystem;

DataLayer::DataLayer()
{
}

QSettings DataLayer::settings()
{
   const auto orga{ QCoreApplication::organizationName() };
   const auto app{ QCoreApplication::applicationName() };
   return QSettings(orga, app);
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
   emit currentMatrixChanged();
}

cv::Mat DataLayer::currentMatrix(MatrixLayer layer)
{
   return m_matrixManger.getSourceData(layer);
}

MatrixPropertyList DataLayer::currentPropertyList(MatrixLayer layer)
{
   return m_matrixManger.getMatrixPropertyList(layer);
}

const MatrixFileRepository& DataLayer::getFileRepository() const
{
   return m_fileManger.getFileList();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
