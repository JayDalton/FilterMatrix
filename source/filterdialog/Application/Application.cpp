#include <precompheader.h>

#include "Logger/Logger.h"
#include "Application.h"

#include <string_view>

namespace fs = std::filesystem;

Application::Application(int argc, char* argv[], std::string_view title)
   : QApplication(argc, argv), m_data(std::make_shared<DataLayer>())
{
   QCoreApplication::setOrganizationName("LegalDuplics");
   QCoreApplication::setApplicationName(title.data());

   setupLogger();
   setupDialog();

   auto con = connect(this, &QApplication::lastWindowClosed, this, &QApplication::quit);

   m_dialog->show();
}

void Application::setConfig(const ApplicationConfig& config)
{
   m_config = config;
}

void Application::setupLogger()
{
   fs::path path("logfiles/dialog.log");
   if (!fs::exists(path))
   {
      auto p = path.parent_path();
      fs::create_directories(p);
   }

   auto file_logger = spdlog::basic_logger_mt("logger", path.string());
   spdlog::set_default_logger(file_logger);
   //spdlog::set_level(spdlog::level::debug);
   spdlog::flush_every(std::chrono::seconds(3));
   spdlog::flush_on(spdlog::level::warn);

   const auto app = QCoreApplication::applicationName().toStdString();
   const auto ver = QCoreApplication::applicationVersion().toStdString();
   spdlog::info("===============================================");
   spdlog::info("Logging: {0} - {1}", app, ver);
   spdlog::info("===============================================");
}

void Application::setupDialog()
{
   m_dialog = std::make_unique<FilterDialog>(m_data);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
