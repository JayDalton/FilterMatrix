/********************************************************************************
** Form generated from reading UI file 'MatrixDataTab.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXDATATAB_H
#define UI_MATRIXDATATAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixDataTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPoint;
    QSpinBox *spinBoxPointX;
    QSpinBox *spinBoxPointY;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelRange;
    QSpinBox *spinBoxSizeW;
    QSpinBox *spinBoxSizeH;
    QTreeView *treePropertyView;

    void setupUi(QWidget *MatrixDataTab)
    {
        if (MatrixDataTab->objectName().isEmpty())
            MatrixDataTab->setObjectName(QString::fromUtf8("MatrixDataTab"));
        MatrixDataTab->resize(958, 535);
        horizontalLayout = new QHBoxLayout(MatrixDataTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeView = new QTreeView(MatrixDataTab);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        horizontalLayout->addWidget(treeView);

        groupBox = new QGroupBox(MatrixDataTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelPoint = new QLabel(groupBox);
        labelPoint->setObjectName(QString::fromUtf8("labelPoint"));

        horizontalLayout_2->addWidget(labelPoint);

        spinBoxPointX = new QSpinBox(groupBox);
        spinBoxPointX->setObjectName(QString::fromUtf8("spinBoxPointX"));
        spinBoxPointX->setMaximum(5000);

        horizontalLayout_2->addWidget(spinBoxPointX);

        spinBoxPointY = new QSpinBox(groupBox);
        spinBoxPointY->setObjectName(QString::fromUtf8("spinBoxPointY"));
        spinBoxPointY->setMaximum(5000);

        horizontalLayout_2->addWidget(spinBoxPointY);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelRange = new QLabel(groupBox);
        labelRange->setObjectName(QString::fromUtf8("labelRange"));

        horizontalLayout_3->addWidget(labelRange);

        spinBoxSizeW = new QSpinBox(groupBox);
        spinBoxSizeW->setObjectName(QString::fromUtf8("spinBoxSizeW"));
        spinBoxSizeW->setMaximum(5000);

        horizontalLayout_3->addWidget(spinBoxSizeW);

        spinBoxSizeH = new QSpinBox(groupBox);
        spinBoxSizeH->setObjectName(QString::fromUtf8("spinBoxSizeH"));
        spinBoxSizeH->setMaximum(5000);

        horizontalLayout_3->addWidget(spinBoxSizeH);


        verticalLayout->addLayout(horizontalLayout_3);

        treePropertyView = new QTreeView(groupBox);
        treePropertyView->setObjectName(QString::fromUtf8("treePropertyView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treePropertyView->sizePolicy().hasHeightForWidth());
        treePropertyView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(treePropertyView);


        horizontalLayout->addWidget(groupBox);


        retranslateUi(MatrixDataTab);

        QMetaObject::connectSlotsByName(MatrixDataTab);
    } // setupUi

    void retranslateUi(QWidget *MatrixDataTab)
    {
        MatrixDataTab->setWindowTitle(QCoreApplication::translate("MatrixDataTab", "MatrixDataTab", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MatrixDataTab", "Eigenschaften", nullptr));
        labelPoint->setText(QCoreApplication::translate("MatrixDataTab", "Point: X / Y", nullptr));
        labelRange->setText(QCoreApplication::translate("MatrixDataTab", "Range: W / H", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixDataTab: public Ui_MatrixDataTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXDATATAB_H
