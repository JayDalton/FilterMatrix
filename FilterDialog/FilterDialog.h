#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_FilterDialog.h"

class FilterDialog : public QMainWindow
{
    Q_OBJECT

public:
    FilterDialog(QWidget *parent = nullptr);

private:
    Ui::FilterDialogClass ui;
};
