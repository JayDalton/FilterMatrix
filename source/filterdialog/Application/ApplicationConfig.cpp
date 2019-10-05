#include <precompheader.h>

#include "ApplicationConfig.h"

ApplicationConfig::ApplicationConfig()
{
   registerString(DEFAULT_MATRIX_IMPORT, "Standard Datei", "application.cfg");

   registerString(DEFAULT_MATRIX_FOLDER, "Standard Ordner", "...");

   registerString(DEFAULT_LOGFILE_FOLDER, "Logfile Ordner", "...");
}

std::string ApplicationConfig::getDefaultImportMatrix() const
{
   return std::string();
}

std::string ApplicationConfig::getDefaultMatrixFolder() const
{
   return std::string();
}


/*

{
   "application" : "",
   "app-version" : "",
   "matrixImport" : "",
   "matrixFolder" : ""
}

*/


// Codepage: UTF-8 (ÜüÖöÄäẞß)

