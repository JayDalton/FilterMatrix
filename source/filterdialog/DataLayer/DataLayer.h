#pragma once

#include <memory>


struct DataLayer
{
   explicit DataLayer();

   void loadConfiguration();
};

using DataLayerUPtr = std::unique_ptr<DataLayer>;
