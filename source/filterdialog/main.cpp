#include <pch.h>

#include "FilterDialog.h"

#include <QtWidgets/QApplication>

#include "FilterDialog.h"


#include "Application.h"



int main(int argc, char *argv[])
{
   Application application(argc, argv, "");
   //application.setConfig(new EmsClientGuiConfig);
   application.connect(&application, &QApplication::lastWindowClosed, &application, &QApplication::quit);


   QApplication a(argc, argv);
   FilterDialog w;
   w.show();
   return a.exec();
}
