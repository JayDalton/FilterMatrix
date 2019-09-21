/********************************************************************************
** Form generated from reading UI file 'MatrixDataTab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXDATATAB_H
#define UI_MATRIXDATATAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixDataTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;

    void setupUi(QWidget *MatrixDataTab)
    {
        if (MatrixDataTab->objectName().isEmpty())
            MatrixDataTab->setObjectName(QString::fromUtf8("MatrixDataTab"));
        MatrixDataTab->resize(865, 476);
        horizontalLayout = new QHBoxLayout(MatrixDataTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeView = new QTreeView(MatrixDataTab);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        horizontalLayout->addWidget(treeView);


        retranslateUi(MatrixDataTab);

        QMetaObject::connectSlotsByName(MatrixDataTab);
    } // setupUi

    void retranslateUi(QWidget *MatrixDataTab)
    {
        MatrixDataTab->setWindowTitle(QApplication::translate("MatrixDataTab", "MatrixDataTab", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixDataTab: public Ui_MatrixDataTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXDATATAB_H
