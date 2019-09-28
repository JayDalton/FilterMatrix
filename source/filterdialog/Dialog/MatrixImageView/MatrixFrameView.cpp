#include "precompheader.h"

#include "MatrixImageView/MatrixFrameView.h"

MatrixFrameView::MatrixFrameView(QWidget* parent)
   : QFrame(parent)
{

}

void MatrixFrameView::setImageMatrix(const cv::Mat& matrix)
{
   m_matrix = matrix;
   m_bitmapImage = coverMatrixByImage(matrix);
   m_contentRect = m_bitmapImage.rect();
}

void MatrixFrameView::paintEvent(QPaintEvent* event)
{
   QFrame::paintEvent(event);

   if (m_matrix.empty())
   {
      return;
   }

   QPainter painter(this);

   QPen pen(Qt::cyan);

   painter.setPen(pen);
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
   //preparePainterImagePlane(_painter, _render, true);
   painter.drawImage(QPoint(0,0), m_bitmapImage);

   painter.drawRect(QRect(0, 0, 200, 200));
}

QImage MatrixFrameView::coverMatrixByImage(const cv::Mat& _matrix)
{
   const QHash<int, QImage::Format> formats = {
      {CV_8UC1, QImage::Format_Grayscale8},
      //{CV_16UC1, QImage::Format_Grayscale16},
   };

   const auto format{ _matrix.type() };
   if (!formats.contains(format))
   {
      qDebug() << "DPImageHelper::coverMatrixToImage - wrong image format";
      return {};
   }

   return QImage(
      _matrix.data, _matrix.cols, _matrix.rows,
      static_cast<int>(_matrix.step), formats[format]
   );
}
