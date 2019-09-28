#include <precompheader.h>

#include "Logger/Logger.h"
#include "Application.h"

#include <string_view>

namespace fs = std::filesystem;

Application::Application(int argc, char* argv[], std::string_view title)
   : QApplication(argc, argv), m_data(std::make_shared<DataLayer>()), m_dialog(m_data)
{
   setOrganizationName("legal duplics");
   setApplicationName(title.empty() ? QFileInfo(QCoreApplication::applicationFilePath()).baseName() : title.data());

   setupLogger();
   setupDialog();

   auto con = connect(this, &QApplication::lastWindowClosed, this, &QApplication::quit);

   m_dialog.show();
}

void Application::setConfig()
{
}

void Application::setupLogger()
{
   fs::path path("logs/dialog.log");
   if (!fs::exists(path))
   {
      auto p = path.parent_path();
      fs::create_directories(p);
   }

   // Set the default logger to file logger
   auto file_logger = spdlog::basic_logger_mt("logger", path.string(), true);
   spdlog::set_default_logger(file_logger);
   
   spdlog::set_level(spdlog::level::debug);
   spdlog::flush_every(std::chrono::seconds(1));

   //spdlog::debug("This message should be displayed..");    

   //spdlog::info("Welcome to spdlog!");
   //spdlog::error("Some error message with arg: {}", 1);
   //spdlog::debug("This message should be displayed..");    
   //spdlog::warn("Easy padding in numbers like {:08d}", 12);
   //spdlog::info("Support for floats {:03.2f}", 1.23456);
   //spdlog::info("Positional args are {1} {0}..", "too", "supported");


   //spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
}

void Application::setupDialog()
{
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
