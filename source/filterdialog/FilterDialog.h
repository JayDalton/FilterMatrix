#pragma once

#include <QtWidgets/QWidget>
#include "ui_FilterDialog.h"

class FilterDialog : public QWidget
{
    Q_OBJECT

public:
    FilterDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::FilterDialogClass ui;
};
