#pragma once

#include <QWidget>

#include "DataLayer/DataLayer.h"
#include <Dialog\FileSelect\FileSelectModel.h>

class FileSelectTab : public QWidget
{
    Q_OBJECT

public:
    ~FileSelectTab() = default;
    explicit FileSelectTab(DataLayerSPtr data, QWidget* parent);

signals:
   void displayMatrixData();

protected:
   void contextMenuEvent(QContextMenuEvent* event) override;

private:
   void setupUIElements();
   void setupActions();
   void setupMenus();

   void openFile();
   void loadFile();
   void saveFile();

   void editConfig();

private:
   struct Impl;
   std::unique_ptr<Impl> m;

   FileSelectModelPtr m_fileSelectModel{ nullptr };
   FileSelectProxyPtr m_fileSelectProxy{ nullptr };
};
