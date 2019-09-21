#pragma once

#include <QWidget>

#include "DataLayer/DataLayer.h"

class FileSelectTab : public QWidget
{
    Q_OBJECT

public:
    ~FileSelectTab() = default;
    explicit FileSelectTab(DataLayerSPtr data, QWidget* parent);

protected:
   void contextMenuEvent(QContextMenuEvent* event) override;

private:
   void setupUIElements();
   void setupActions();
   void setupMenus();

   void openFile();
   void saveFile();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
