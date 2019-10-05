#pragma once

#include <optional>

#include "Dialog/FilterDialog.h"

#include "Application/ApplicationConfig.h"

#include <QApplication>

using FileLogger = std::shared_ptr<spdlog::logger>;

class Application : public QApplication
{
   Q_OBJECT

public:
   Application(int argc, char* argv[], std::string_view title);

   void setConfig(const ApplicationConfig& config);

private:
   void setupLogger();
   void setupDialog();

private:
   ApplicationConfig m_config;
   DataLayerSPtr m_data{ nullptr };
   FilterDialogUPtr m_dialog{ nullptr };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
