/********************************************************************************
** Form generated from reading UI file 'MatrixDataPlot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXDATAPLOT_H
#define UI_MATRIXDATAPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QCustomPlot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MatrixDataPlot
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *customPlot;
    QVBoxLayout *verticalLayout;
    QTreeView *layerView;

    void setupUi(QWidget *MatrixDataPlot)
    {
        if (MatrixDataPlot->objectName().isEmpty())
            MatrixDataPlot->setObjectName(QString::fromUtf8("MatrixDataPlot"));
        MatrixDataPlot->resize(629, 417);
        horizontalLayout = new QHBoxLayout(MatrixDataPlot);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        customPlot = new QCustomPlot(MatrixDataPlot);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(customPlot);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layerView = new QTreeView(MatrixDataPlot);
        layerView->setObjectName(QString::fromUtf8("layerView"));

        verticalLayout->addWidget(layerView);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MatrixDataPlot);

        QMetaObject::connectSlotsByName(MatrixDataPlot);
    } // setupUi

    void retranslateUi(QWidget *MatrixDataPlot)
    {
        MatrixDataPlot->setWindowTitle(QApplication::translate("MatrixDataPlot", "MatrixDataPlot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixDataPlot: public Ui_MatrixDataPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXDATAPLOT_H
