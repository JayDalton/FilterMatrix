#pragma once

#include <QImage>
#include <QFrame>
#include <QRect>

#include "DataLayer/DataLayer.h"
#include "MatrixImage.h"

class MatrixFrameView : public QFrame
{
   Q_OBJECT
public:
   explicit MatrixFrameView(QWidget* parent);

   void setImageMatrix(const cv::Mat& matrix);

   void setScaleValue(double value);
   void setTranslateX(double value);
   void setTranslateY(double value);

protected:
   void paintEvent(QPaintEvent* event) override;
   //void mouseDoubleClickEvent(QMouseEvent* event);
   void mousePressEvent(QMouseEvent* event);
   void mouseMoveEvent(QMouseEvent* event);
   void mouseReleaseEvent(QMouseEvent* event);
   void wheelEvent(QWheelEvent* event) override;

private:
   void setDisplayRect(const QRect& display);
   QImage coverMatrixByImage(const cv::Mat& _matrix) const;
   QTransform createTransform() const;
   void updateTransform();

   void scaleArea(double factor);

private:
   cv::Mat m_matrix;
   QRectF m_displayRect;
   QRectF m_visibleRect;
   QRectF m_contentRect;
   QImage m_bitmapImage;
   QImage m_bitmapOverlay;
   QTransform m_transform;

   bool m_mouseActive{ false };
};

