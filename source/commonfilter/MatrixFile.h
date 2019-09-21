#pragma once

#include <array>
#include <string>
#include <optional>
#include <filesystem>
#include <string_view>

namespace fs = std::filesystem;

struct MatrixFileInfo
{
   enum class Type { None, Graymap, Count };

   explicit MatrixFileInfo(std::string_view filePath);

   const fs::path& getPath() const;

   bool isValid() const;
   Type getFileType() const;
   unsigned getFileSize() const;
   std::string getFileName() const;
   std::string getFilePath() const;
   std::string getExtension() const;

private:
   fs::path m_path;
   static inline const std::array<std::string, 1> m_validExtensions{".pgm"};
};

using MatrixFileUPtr = std::unique_ptr<MatrixFileInfo>;
using MatrixFileSPtr = std::shared_ptr<MatrixFileInfo>;
using MatrixFileList = std::vector<MatrixFileInfo>;
using MatrixFileOpt = std::optional<MatrixFileInfo>;

using MatrixFileRepository = std::vector<MatrixFileInfo>;

