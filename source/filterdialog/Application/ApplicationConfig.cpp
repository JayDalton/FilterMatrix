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

   registerListParameter(ListParameter{
      MATRIX_FOLDER_FILELIST, "Standard Datei Liste", 
      {
         "path/to/next/sub/folder/1"s,
         "path/to/next/sub/folder/2"s,
         "path/to/next/sub/folder/3"s,
         "path/to/next/sub/folder/4"s,
      }
   });
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
   return getStringParameter(DEFAULT_MATRIX_FOLDER);
}

void ApplicationConfig::setDefaultMatrixFolder(std::string_view file)
{
}

std::vector<std::string> ApplicationConfig::getFolderFilelist() const
{
   const ListParameter& param = getListParameter(MATRIX_FOLDER_FILELIST);
   //if (std::holds_alternative<std::vector<std::string>>(param.m_current))
   //{
   //   return std::get<ListParameter>(param);
   //}
   return std::vector<std::string>();
}

void ApplicationConfig::setFolderFilelist(const std::vector<std::string>& list)
{
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)

