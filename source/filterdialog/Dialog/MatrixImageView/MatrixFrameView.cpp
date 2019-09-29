#include "precompheader.h"

#include "MatrixImageView/MatrixFrameView.h"

#include "Logger/Logger.h"

MatrixFrameView::MatrixFrameView(QWidget* parent)
   : QFrame(parent)
{
}

void MatrixFrameView::setImageMatrix(const cv::Mat& matrix)
{
   m_matrix = matrix;
   m_bitmapImage = coverMatrixByImage(matrix);
   m_contentRect = m_bitmapImage.rect();
   m_visibleRect = m_bitmapImage.rect();
}

void MatrixFrameView::setScaleValue(double value)
{
   QTransform transform;
   transform.scale(value, value);
   m_visibleRect = transform.mapRect(m_visibleRect);
}

void MatrixFrameView::setTranslateX(double value)
{
   QTransform transform;
   transform.translate(value, 0);
   m_visibleRect = transform.mapRect(m_visibleRect);
}

void MatrixFrameView::setTranslateY(double value)
{
   QTransform transform;
   transform.translate(0, value);
   m_visibleRect = transform.mapRect(m_visibleRect);
}

void MatrixFrameView::paintEvent(QPaintEvent* event)
{
   QFrame::paintEvent(event);

   if (m_matrix.empty())
   {
      return;
   }

   setDisplayRect(rect());

   QPainter painter(this);

   painter.setTransform(m_transform);
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
   painter.drawImage(QPoint(0,0), m_bitmapImage);
}

void MatrixFrameView::setDisplayRect(const QRect& display)
{
   m_displayRect = display;
   m_transform = createTransform();
}

QImage MatrixFrameView::coverMatrixByImage(const cv::Mat& _matrix) const
{
   const QHash<int, QImage::Format> formats = {
      {CV_8UC1, QImage::Format_Grayscale8},
      {CV_16UC1, QImage::Format_Grayscale16},
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

QTransform MatrixFrameView::createTransform() const
{
   QTransform transform;
   if (m_matrix.empty()) return transform;

   m_contentRect;
   m_visibleRect;

   // Berechnungen
   const auto translate{m_displayRect.center() - m_visibleRect.center()};

   const auto scaleW{ m_displayRect.width() / m_visibleRect.width() };
   const auto scaleH{ m_displayRect.height() / m_visibleRect.height() };
   const auto [minimum, maximum] { std::minmax(scaleW, scaleH) };

   // Transformation
   transform.translate(m_displayRect.center().x(), m_displayRect.center().y());
   transform.scale(minimum, minimum);
   transform.translate(translate.x(), translate.y());
   transform.translate(-m_displayRect.center().x(), -m_displayRect.center().y());

   return transform;
}

void MatrixFrameView::updateTransform()
{
   m_transform = createTransform();
}
