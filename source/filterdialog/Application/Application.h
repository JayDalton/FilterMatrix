#pragma once

#include <qapplication.h>

class Application : public QApplication
{
   Q_OBJECT

public:
   Application(int argc, char* argv[], std::string_view title = {});

   void setConfig();
};

