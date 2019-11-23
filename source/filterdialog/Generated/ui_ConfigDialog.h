/********************************************************************************
** Form generated from reading UI file 'ConfigDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;

    void setupUi(QWidget *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QString::fromUtf8("ConfigDialog"));
        ConfigDialog->resize(400, 300);
        gridLayout = new QGridLayout(ConfigDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(ConfigDialog);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);


        retranslateUi(ConfigDialog);

        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QWidget *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QCoreApplication::translate("ConfigDialog", "ConfigDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
