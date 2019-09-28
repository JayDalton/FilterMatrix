#pragma once

#include "Dialog/FilterDialog.h"
#include "Logger/Logger.h"
#include <spdlog/logger.h>
#include <QApplication>

using FileLogger = std::shared_ptr<spdlog::logger>;

class Application : public QApplication
{
   Q_OBJECT

public:
   Application(int argc, char* argv[], std::string_view title);

   void setConfig();

   void log();

private:
   void setupLogger();
   void setupDialog();

private:
   DataLayerSPtr m_data{ nullptr };
   FilterDialog m_dialog;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
