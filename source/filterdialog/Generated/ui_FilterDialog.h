/********************************************************************************
** Form generated from reading UI file 'FilterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERDIALOG_H
#define UI_FILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterDialogClass
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *FilterDialogClass)
    {
        if (FilterDialogClass->objectName().isEmpty())
            FilterDialogClass->setObjectName(QString::fromUtf8("FilterDialogClass"));
        FilterDialogClass->resize(600, 400);
        gridLayout = new QGridLayout(FilterDialogClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(FilterDialogClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(FilterDialogClass);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(FilterDialogClass);
    } // setupUi

    void retranslateUi(QWidget *FilterDialogClass)
    {
        FilterDialogClass->setWindowTitle(QApplication::translate("FilterDialogClass", "FilterDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterDialogClass: public Ui_FilterDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERDIALOG_H
