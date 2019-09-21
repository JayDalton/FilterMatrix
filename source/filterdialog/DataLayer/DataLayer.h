#pragma once

#include <memory>
#include <string>
#include <vector>

#include "FileManager.h"
#include "MatrixManager.h"

struct DataLayer
{
   explicit DataLayer();

   void loadConfiguration();

   bool readMatrixFileInfo(const StringVector& pathList);
   bool readMatrixFileInfo(std::string_view path);

   void loadMatrixFile(MatrixFileInfo file);

   cv::Mat currentMatrix();

   const MatrixFileRepository& getFileRepository() const;

   void getSourceMatrixView();
   void getMagnitudeMatrixView();
   void getResultMatrixView();

private:
   FileManager m_fileManger;
   MatrixManager m_matrixManger;
};

using DataLayerUPtr = std::unique_ptr<DataLayer>;
using DataLayerSPtr = std::shared_ptr<DataLayer>;
