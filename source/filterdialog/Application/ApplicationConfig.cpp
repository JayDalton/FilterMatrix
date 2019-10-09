#include <precompheader.h>

#include "ApplicationConfig.h"

ApplicationConfig::ApplicationConfig()
   /*: Configuration{ std::string{""}, std::string{""} }*/
{
   registerBaseParameter(BaseParameter{ 
      DEFAULT_MATRIX_IMPORT, "Standard Matrix Datei", 
      std::string{"current"}, 4096, 0
      }
   );

   registerBaseParameter(BaseParameter{ 
      DEFAULT_MATRIX_FOLDER, "Standard Matrix Ordner", 
      fs::path{"application.cfg"}, 4096, 0
      }
   );

   registerBaseParameter(BaseParameter{ 
      DEFAULT_LOGFILE_FOLDER, "Standard Logfile", 
      fs::path{"logfiles/dialog.log"}, 4096, 0
      }
   );

   ListParameter list{ "", "", { std::string(), std::string()} };

   //registerParameter(Parameter{ "filePathList", "Dateiliste", Parameter::ValueList{
   //   Parameter{ "filePath1", "Datei Pfad 1", fs::path{"logfiles/dialog.log"} },
   //   Parameter{ "filePath2", "Datei Pfad 2", fs::path{"logfiles/dialog.log"} },
   //   Parameter{ "filePath3", "Datei Pfad 3", fs::path{"logfiles/dialog.log"} },
   //   Parameter{ "filePath4", "Datei Pfad 4", fs::path{"logfiles/dialog.log"} },
   //   Parameter{ "filePath5", "Datei Pfad 5", fs::path{"logfiles/dialog.log"} },
   //   } }
   //);


   registerBaseParameter(BaseParameter{ "signed", "label", -1234 });
   registerBaseParameter(BaseParameter{ "unsigned", "label", 1234u });
   registerBaseParameter(BaseParameter{ "double", "label", 3.21 });
   registerBaseParameter(BaseParameter{ "boolean", "bool", true });
   registerBaseParameter(BaseParameter{ "string", "label", std::string{"23"} });
   registerBaseParameter(BaseParameter{ "path", "label", fs::path{"top/sub"} });
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

