#pragma once

#include <QtWidgets/QWidget>

class FilterDialog : public QWidget
{
    Q_OBJECT

public:
   ~FilterDialog();
   explicit FilterDialog();

protected:
   void closeEvent(QCloseEvent* event) override;

private:
   void setupDataLayers();
   void setupTabWidgets();
   void restoreSettings();
   void saveSettings();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
