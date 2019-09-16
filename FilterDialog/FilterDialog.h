#pragma once

#include "ui_FilterDialog.h"

#include <QtWidgets/QMainWindow>

class FilterDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilterDialog();
    ~FilterDialog();

protected:
   void contextMenuEvent(QContextMenuEvent* event) override;

private:
   void setupActions();
   void setupMenus();

   void openFile();
   void saveFile();

private:
   struct Impl;
   std::unique_ptr<Impl> m;

   Ui::FilterDialogClass ui;

   std::unique_ptr<QAction> m_openFile{nullptr};
   std::unique_ptr<QAction> m_saveFile{nullptr};
};
