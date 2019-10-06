#include <precompheader.h>
#include <variant>
#include "ApplicationConfig.h"

ApplicationConfig::ApplicationConfig()
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

std::string ApplicationConfig::getDefaultImportMatrix()
{
   const auto& param = getParameter(DEFAULT_MATRIX_IMPORT);
   if (auto value = std::get_if<std::string>(&param.m_current))
   {
      return *value;
   }

   if (std::holds_alternative<std::string>(param.m_current))
   {
      return std::get<std::string>(param.m_current);
   }

   if (auto option = getParameterOpt(DEFAULT_MATRIX_IMPORT))
   {
      if (auto value = std::get_if<std::string>(&(*option).m_current))
      {

      }

   }

   assert(false);

   return {};
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

