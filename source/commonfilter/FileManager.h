#pragma once

#include <memory>
#include <string>
#include <string_view>


struct FileManager
{
   FileManager();

   void loadMatrixFromFile(std::string_view path) const;


};

using FileManagerUPtr = std::unique_ptr<FileManager>;
using FileManagerSPtr = std::shared_ptr<FileManager>;
