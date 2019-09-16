#include <pch.h>

#include "Application/Application.h"
#include "Dialog/FilterDialog.h"

int main(int argc, char *argv[])
{
   Application application(argc, argv, "Matrix Filter");
   //application.setConfig(FilterDialogGuiConfig{});
   application.connect(&application, &QApplication::lastWindowClosed, &application, &QApplication::quit);


   FilterDialog dialog;
   //dialog.setConfig(FilterDialogConfig{});
   dialog.show();

   return application.exec();
}
