#include "precompheader.h"

#include "MatrixImageView/MatrixFrameView.h"

#include <QPainter>

MatrixFrameView::MatrixFrameView(QWidget* parent)
   : QFrame(parent)
{

}

void MatrixFrameView::paintEvent(QPaintEvent* event)
{
   QFrame::paintEvent(event);

   QPainter painter(this);

   QPen pen(Qt::cyan);

   painter.setPen(pen);
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
   //preparePainterImagePlane(_painter, _render, true);
   //painter.drawImage(QPoint(0,0), _render->image());

   painter.drawRect(QRect(0, 0, 200, 200));
}

