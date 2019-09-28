/********************************************************************************
** Form generated from reading UI file 'MatrixImageView.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXIMAGEVIEW_H
#define UI_MATRIXIMAGEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "MatrixImageView/MatrixFrameView.h"

QT_BEGIN_NAMESPACE

class Ui_MatrixImageView
{
public:
    QGridLayout *gridLayout;
    MatrixFrameView *frameView;

    void setupUi(QWidget *MatrixImageView)
    {
        if (MatrixImageView->objectName().isEmpty())
            MatrixImageView->setObjectName(QString::fromUtf8("MatrixImageView"));
        MatrixImageView->resize(588, 400);
        gridLayout = new QGridLayout(MatrixImageView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frameView = new MatrixFrameView(MatrixImageView);
        frameView->setObjectName(QString::fromUtf8("frameView"));
        frameView->setFrameShape(QFrame::StyledPanel);
        frameView->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameView, 0, 0, 1, 1);


        retranslateUi(MatrixImageView);

        QMetaObject::connectSlotsByName(MatrixImageView);
    } // setupUi

    void retranslateUi(QWidget *MatrixImageView)
    {
        MatrixImageView->setWindowTitle(QApplication::translate("MatrixImageView", "MatrixImageView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixImageView: public Ui_MatrixImageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXIMAGEVIEW_H
