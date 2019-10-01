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

void MatrixFrameView::scaleArea(double _factor)
{
   qDebug() << "old factor:" << _factor;
   auto factor = std::max(0.05, std::min(50.0, _factor));
   qDebug() << "new factor:" << factor;

   auto w = m_displayRect.width() * factor;
   auto w2 = qRound(w * 0.5);
   auto h = m_displayRect.height() * factor;
   auto h2 = qRound(h * 0.5);
   auto c = m_displayRect.center();
   m_displayRect.setLeft(c.x()-w2);
   m_displayRect.setRight(c.x()+w2);
   m_displayRect.setTop(c.y()-h2);
   m_displayRect.setBottom(c.y()+h2);
   qDebug() << "new display rect:" << m_displayRect;

}

void MatrixFrameView::setScaleValue(double value)
{
   QTransform transform;
   transform.scale(value, value);
   qDebug() << "value:" << value;
   m_visibleRect = transform.mapRect(m_visibleRect);
   qDebug() << "new rect:" << m_visibleRect;
   update();
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

   QPainter painter(this);

   if (m_matrix.empty())
   {
      painter.drawRect(rect());
      return;
   }

   setDisplayRect(rect());

   painter.setTransform(m_transform);
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
   painter.drawImage(QPoint(0,0), m_bitmapImage);
}

void MatrixFrameView::mousePressEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton) 
   {
      //lastPoint = event->pos();
      m_mouseActive = true;
   }
}

void MatrixFrameView::mouseMoveEvent(QMouseEvent *event)
{
   if ((event->buttons() & Qt::LeftButton) && m_mouseActive)
   {
      //drawLineTo(event->pos());
   }
}

void MatrixFrameView::mouseReleaseEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton && m_mouseActive) 
   {
      //drawLineTo(event->pos());
      m_mouseActive = false;
   }
}

void MatrixFrameView::wheelEvent(QWheelEvent* event)
{
   QPoint numPixels = event->pixelDelta();
   QPoint numDegrees = event->angleDelta() / 8;

   if (!numPixels.isNull()) 
   {
      qDebug() << numPixels;
      //scrollWithPixels(numPixels);
   
   } else if (!numDegrees.isNull()) 
   {
      QPoint numSteps = numDegrees / 15;
      qDebug() << numSteps;
      //scrollWithDegrees(numSteps);
   }

   qDebug() << event->posF();

   event->accept();
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

