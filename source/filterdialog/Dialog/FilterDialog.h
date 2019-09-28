#pragma once

#include "DataLayer/DataLayer.h"

#include <QtWidgets/QWidget>

class FilterDialog : public QWidget
{
    Q_OBJECT

public:
   explicit FilterDialog(DataLayerSPtr data);
   ~FilterDialog();

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
