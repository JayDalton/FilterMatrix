#pragma once

#include "Config/ConfigParameter.h"
#include "Config/Configuration.h"
#include "Config/ValueVisitor.h"

struct ApplicationConfig : public Configuration
{
   ApplicationConfig();
   ~ApplicationConfig();

   std::string getDefaultImportMatrix() const;
   void setDefaultImportMatrix(const std::string& file);

   std::string getDefaultMatrixFolder() const;
   void setDefaultMatrixFolder(std::string_view file);


private:
   static constexpr char* DEFAULT_MATRIX_IMPORT{"matrixImport"};
   static constexpr char* DEFAULT_MATRIX_FOLDER{"matrixFolder"};
   static constexpr char* DEFAULT_LOGFILE_FOLDER{"loggingFolder"};
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
