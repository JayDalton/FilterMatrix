#include <precompheader.h>

#include "Application/Application.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");

   ApplicationConfig config;
   fs::path filePath{ "filterdialog.cfg" };
   if (config.loadJsonFile(filePath))
   {
      application.setConfig(config);
   }

   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
