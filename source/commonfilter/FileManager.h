#pragma once

#include <memory>
#include <string>
#include <optional>
#include <string_view>

#include "MatrixFile.h"

using StringVector = std::vector<std::string>;

struct FileManager
{
   bool loadMatrixFileInfo(std::string_view filePath);
   bool loadMatrixFileInfo(const StringVector& fileList);

   void appendMatrixFile(MatrixFileInfo matrixFile);
   void appendMatrixFileList(MatrixFileList fileList);

   const MatrixFileList& getFileList() const;

private:
   MatrixFileList m_fileList;
};

using FileManagerUPtr = std::unique_ptr<FileManager>;
using FileManagerSPtr = std::shared_ptr<FileManager>;
