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

protected:
   void paintEvent(QPaintEvent* event) override;

private:
   QImage coverMatrixByImage(const cv::Mat& _matrix);

private:
   cv::Mat m_matrix;
   QRect m_contentRect;
   QImage m_bitmapImage;
};

