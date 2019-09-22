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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QLabel *labelRange;
    QLineEdit *lineEditRange;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelMinimum;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_3;
    QTreeView *treePropertyView;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelMaximum;
    QLabel *labelMaxValue;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAverage;
    QLabel *labelAvgValue;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLabel *label_4;

    void setupUi(QWidget *MatrixDataTab)
    {
        if (MatrixDataTab->objectName().isEmpty())
            MatrixDataTab->setObjectName(QString::fromUtf8("MatrixDataTab"));
        MatrixDataTab->resize(923, 532);
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
        labelRange = new QLabel(groupBox);
        labelRange->setObjectName(QString::fromUtf8("labelRange"));

        horizontalLayout_2->addWidget(labelRange);

        lineEditRange = new QLineEdit(groupBox);
        lineEditRange->setObjectName(QString::fromUtf8("lineEditRange"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditRange->sizePolicy().hasHeightForWidth());
        lineEditRange->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEditRange);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelMinimum = new QLabel(groupBox);
        labelMinimum->setObjectName(QString::fromUtf8("labelMinimum"));

        horizontalLayout_3->addWidget(labelMinimum);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(5000);

        horizontalLayout_3->addWidget(spinBox);

        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMaximum(5000);

        horizontalLayout_3->addWidget(spinBox_2);

        spinBox_4 = new QSpinBox(groupBox);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setMaximum(5000);

        horizontalLayout_3->addWidget(spinBox_4);

        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setMaximum(5000);

        horizontalLayout_3->addWidget(spinBox_3);


        verticalLayout->addLayout(horizontalLayout_3);

        treePropertyView = new QTreeView(groupBox);
        treePropertyView->setObjectName(QString::fromUtf8("treePropertyView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treePropertyView->sizePolicy().hasHeightForWidth());
        treePropertyView->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(treePropertyView);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelMaximum = new QLabel(groupBox);
        labelMaximum->setObjectName(QString::fromUtf8("labelMaximum"));

        horizontalLayout_6->addWidget(labelMaximum);

        labelMaxValue = new QLabel(groupBox);
        labelMaxValue->setObjectName(QString::fromUtf8("labelMaxValue"));

        horizontalLayout_6->addWidget(labelMaxValue);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelAverage = new QLabel(groupBox);
        labelAverage->setObjectName(QString::fromUtf8("labelAverage"));

        horizontalLayout_5->addWidget(labelAverage);

        labelAvgValue = new QLabel(groupBox);
        labelAvgValue->setObjectName(QString::fromUtf8("labelAvgValue"));

        horizontalLayout_5->addWidget(labelAvgValue);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout->addWidget(groupBox);


        retranslateUi(MatrixDataTab);

        QMetaObject::connectSlotsByName(MatrixDataTab);
    } // setupUi

    void retranslateUi(QWidget *MatrixDataTab)
    {
        MatrixDataTab->setWindowTitle(QApplication::translate("MatrixDataTab", "MatrixDataTab", nullptr));
        groupBox->setTitle(QApplication::translate("MatrixDataTab", "Eigenschaften", nullptr));
        labelRange->setText(QApplication::translate("MatrixDataTab", "Ausschnitt", nullptr));
        lineEditRange->setText(QApplication::translate("MatrixDataTab", "(P1/P2)[123,456/789,123]", nullptr));
        labelMinimum->setText(QApplication::translate("MatrixDataTab", "Ausschnitt", nullptr));
        labelMaximum->setText(QApplication::translate("MatrixDataTab", "Maximum", nullptr));
        labelMaxValue->setText(QApplication::translate("MatrixDataTab", "TextLabel", nullptr));
        labelAverage->setText(QApplication::translate("MatrixDataTab", "Average", nullptr));
        labelAvgValue->setText(QApplication::translate("MatrixDataTab", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("MatrixDataTab", "TextLabel", nullptr));
        label_4->setText(QApplication::translate("MatrixDataTab", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixDataTab: public Ui_MatrixDataTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXDATATAB_H
