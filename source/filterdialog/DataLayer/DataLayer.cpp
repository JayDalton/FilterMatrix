#include <pch.h>

#include "DataLayer/DataLayer.h"

namespace fs = std::filesystem;

DataLayer::DataLayer()
{
}

void DataLayer::loadConfiguration()
{
}

bool DataLayer::loadMatrixFile(std::string_view importFileName)
{
   auto path{ fs::path(importFileName) };
   if (!fs::exists(path))
   {
      std::cout << " file does not exist: " << path << std::endl;
      return false;
   }

   if (!path.has_extension() || path.extension() != ".pgm")
   {
      std::cout << " wrong file extension. Only PGM support." << std::endl;
      return false;
   }


   return false;
}
