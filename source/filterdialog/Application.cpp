#include "Application.h"

Application::Application(int argc, char* argv[], std::string_view title)
   : QApplication(argc, argv)
{
   //setApplicationName(title.isEmpty()?QFileInfo(QCoreApplication::applicationFilePath()).baseName():applicationName);

}
