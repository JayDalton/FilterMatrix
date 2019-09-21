#pragma once

#include <memory>

#include "FileManager.h"
#include "MatrixManager.h"

struct DataLayer
{
   explicit DataLayer();

   void loadConfiguration();

   MatrixFileOpt openMatrixFile(std::string_view path);
   void loadMatrixFile(MatrixFileInfo file);

   cv::Mat currentMatrix();

   void getSourceMatrixView();
   void getMagnitudeMatrixView();
   void getResultMatrixView();

private:
   FileManager m_fileManger;
   MatrixManager m_matrixManger;
};

using DataLayerUPtr = std::unique_ptr<DataLayer>;
using DataLayerSPtr = std::shared_ptr<DataLayer>;
