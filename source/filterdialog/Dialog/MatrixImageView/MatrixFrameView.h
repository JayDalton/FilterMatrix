#pragma once

#include <QFrame>

class MatrixFrameView : public QFrame
{
   Q_OBJECT
public:
   explicit MatrixFrameView(QWidget* parent);

protected:
   void paintEvent(QPaintEvent* event) override;


};

