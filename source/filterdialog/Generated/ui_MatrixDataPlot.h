/********************************************************************************
** Form generated from reading UI file 'MatrixDataPlot.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXDATAPLOT_H
#define UI_MATRIXDATAPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
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
    QSpinBox *layerBox;
    QPushButton *selectButton;
    QPushButton *clearButton;
    QTreeView *selectView;

    void setupUi(QWidget *MatrixDataPlot)
    {
        if (MatrixDataPlot->objectName().isEmpty())
            MatrixDataPlot->setObjectName(QString::fromUtf8("MatrixDataPlot"));
        MatrixDataPlot->resize(908, 524);
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
        layerBox = new QSpinBox(MatrixDataPlot);
        layerBox->setObjectName(QString::fromUtf8("layerBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(layerBox->sizePolicy().hasHeightForWidth());
        layerBox->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(layerBox);

        selectButton = new QPushButton(MatrixDataPlot);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        sizePolicy1.setHeightForWidth(selectButton->sizePolicy().hasHeightForWidth());
        selectButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(selectButton);

        clearButton = new QPushButton(MatrixDataPlot);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        sizePolicy1.setHeightForWidth(clearButton->sizePolicy().hasHeightForWidth());
        clearButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(clearButton);

        selectView = new QTreeView(MatrixDataPlot);
        selectView->setObjectName(QString::fromUtf8("selectView"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(selectView->sizePolicy().hasHeightForWidth());
        selectView->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(selectView);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MatrixDataPlot);

        QMetaObject::connectSlotsByName(MatrixDataPlot);
    } // setupUi

    void retranslateUi(QWidget *MatrixDataPlot)
    {
        MatrixDataPlot->setWindowTitle(QCoreApplication::translate("MatrixDataPlot", "MatrixDataPlot", nullptr));
        selectButton->setText(QCoreApplication::translate("MatrixDataPlot", "Select", nullptr));
        clearButton->setText(QCoreApplication::translate("MatrixDataPlot", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixDataPlot: public Ui_MatrixDataPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXDATAPLOT_H
