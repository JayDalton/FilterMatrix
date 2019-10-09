#pragma once

#include "Config/Configuration.h"

struct ApplicationConfig : public Configuration
{
   ApplicationConfig();

   std::string getDefaultImportMatrix() const;
   void setDefaultImportMatrix(const std::string& file);

   std::string getDefaultMatrixFolder() const;
   void setDefaultMatrixFolder(std::string_view file);

   std::vector<std::string> getFolderFilelist() const;
   void setFolderFilelist(const std::vector<std::string>& list);

private:
   static constexpr char* DEFAULT_MATRIX_IMPORT{"matrixImport"};
   static constexpr char* DEFAULT_MATRIX_FOLDER{"matrixFolder"};
   static constexpr char* DEFAULT_LOGFILE_FOLDER{"loggingFolder"};
   static constexpr char* MATRIX_FOLDER_FILELIST{"folderFileFist"};
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
