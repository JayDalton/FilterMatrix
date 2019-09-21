#pragma once

#include <memory>
#include <string>
#include <optional>
#include <string_view>

#include "MatrixFile.h"

struct FileManager
{
   MatrixFileOpt findMatrixFile(std::string_view filePath) const;
   void appendMatrixFile(MatrixFile matrixFile);
   const MatrixFileList& getFileList() const;

private:
   MatrixFileList m_fileList;
};

using FileManagerUPtr = std::unique_ptr<FileManager>;
using FileManagerSPtr = std::shared_ptr<FileManager>;
