#pragma once

#include <QApplication>

class Application : public QApplication
{
   Q_OBJECT

public:
   Application(int argc, char* argv[], std::string_view title = {});

   void setConfig();

private:
   void setupLogger();
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
