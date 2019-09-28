#include <precompheader.h>

#include "Application/Application.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");
   //application.setConfig(FilterDialogGuiConfig{});

   return application.exec();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
