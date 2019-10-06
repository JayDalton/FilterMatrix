#pragma once

#include "Config/ConfigParameter.h"
#include "Config/Configuration.h"
#include "Config/ValueVisitor.h"

struct ApplicationConfig : public Configuration
{
   ApplicationConfig();
   ~ApplicationConfig();

   std::string getDefaultImportMatrix();

   std::string getDefaultMatrixFolder() const;



private:
   static constexpr char* DEFAULT_MATRIX_IMPORT{"matrixImport"};
   static constexpr char* DEFAULT_MATRIX_FOLDER{"matrixFolder"};
   static constexpr char* DEFAULT_LOGFILE_FOLDER{"loggingFolder"};
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
