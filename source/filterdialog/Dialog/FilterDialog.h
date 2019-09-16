#pragma once

#include <QtWidgets/QWidget>

class FilterDialog : public QWidget
{
    Q_OBJECT

public:
   ~FilterDialog();
   explicit FilterDialog();

private:
   void restoreSettings();
   void setupDataLayers();
   void setupTabWidgets();


private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
