/********************************************************************************
** Form generated from reading UI file 'FileSelectTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESELECTTAB_H
#define UI_FILESELECTTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSelectTab
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTreeView *treeView;

    void setupUi(QWidget *FileSelectTab)
    {
        if (FileSelectTab->objectName().isEmpty())
            FileSelectTab->setObjectName(QString::fromUtf8("FileSelectTab"));
        FileSelectTab->resize(636, 370);
        verticalLayout = new QVBoxLayout(FileSelectTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(FileSelectTab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(FileSelectTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        treeView = new QTreeView(FileSelectTab);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        retranslateUi(FileSelectTab);

        QMetaObject::connectSlotsByName(FileSelectTab);
    } // setupUi

    void retranslateUi(QWidget *FileSelectTab)
    {
        FileSelectTab->setWindowTitle(QApplication::translate("FileSelectTab", "FileSelectTab", nullptr));
        pushButton->setText(QApplication::translate("FileSelectTab", "Hinzuf\303\274gen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileSelectTab: public Ui_FileSelectTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESELECTTAB_H
