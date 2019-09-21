#pragma once

#include <array>
#include <string>
#include <optional>
#include <filesystem>
#include <string_view>

namespace fs = std::filesystem;

struct MatrixFile
{
   enum class Type { None, Graymap, Count };

   explicit MatrixFile(std::string_view filePath);

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

using MatrixFileUPtr = std::unique_ptr<MatrixFile>;
using MatrixFileSPtr = std::shared_ptr<MatrixFile>;
using MatrixFileList = std::vector<MatrixFile>;
using MatrixFileOpt = std::optional<MatrixFile>;
