#pragma once

#include <memory>

#include "FileManager.h"



struct DataLayer
{
   explicit DataLayer();

   void loadConfiguration();

   bool loadMatrixFile(std::string_view path);

private:
   FileManager m_fileManger;
};

using DataLayerUPtr = std::unique_ptr<DataLayer>;
using DataLayerSPtr = std::shared_ptr<DataLayer>;
