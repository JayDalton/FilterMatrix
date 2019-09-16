#include "Application.h"

#include <qfileinfo.h>
#include <string_view>

Application::Application(int argc, char* argv[], std::string_view title)
   : QApplication(argc, argv)
{
   setOrganizationName("legal duplics");
   setApplicationName(title.empty() ? QFileInfo(QCoreApplication::applicationFilePath()).baseName() : title.data());

}
