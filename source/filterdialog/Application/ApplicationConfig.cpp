#include <precompheader.h>
#include <variant>
#include "ApplicationConfig.h"

ApplicationConfig::ApplicationConfig()
   /*: Configuration{ std::string{""}, std::string{""} }*/
{
   registerParameter(Parameter{ 
      DEFAULT_MATRIX_IMPORT, "Standard Matrix Datei", 
      std::string{"current"}, 4096, 0
      }
   );

   registerParameter(Parameter{ 
      DEFAULT_MATRIX_FOLDER, "Standard Matrix Ordner", 
      fs::path{"application.cfg"}, 4096, 0
      }
   );

   registerParameter(Parameter{ 
      DEFAULT_LOGFILE_FOLDER, "Standard Logfile", 
      fs::path{"logfiles/dialog.log"}, 4096, 0
      }
   );

   registerParameter(Parameter{ "signed", "label", 1234 });
   registerParameter(Parameter{ "unsigned", "label", 1234u });
   registerParameter(Parameter{ "float", "label", 3.21f });
   registerParameter(Parameter{ "double", "label", 3.21 });
   registerParameter(Parameter{ "string", "label", std::string{"23"} });
   registerParameter(Parameter{ "path", "label", fs::path{"top/sub"} });
}

ApplicationConfig::~ApplicationConfig()
{

}

std::string ApplicationConfig::getDefaultImportMatrix() const
{
   return getStringParameter(DEFAULT_MATRIX_IMPORT);
}

void ApplicationConfig::setDefaultImportMatrix(const std::string& file)
{
   setParameter(DEFAULT_MATRIX_IMPORT, file);
}

std::string ApplicationConfig::getDefaultMatrixFolder() const
{
   return std::string();
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)

