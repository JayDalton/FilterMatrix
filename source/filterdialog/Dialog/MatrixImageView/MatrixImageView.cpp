#include "precompheader.h"

#include "MatrixImageView.h"
#include "MatrixFrameView.h"

#include "Generated/ui_MatrixImageView.h"

struct MatrixImageView::Impl 
{
   explicit Impl(MatrixImageView* par, DataLayerSPtr data) 
      : parent(par), data(data) {}

   Ui::MatrixImageView ui;
   DataLayerSPtr data{ nullptr };

private:
   MatrixImageView* parent{ nullptr };
};

MatrixImageView::MatrixImageView(DataLayerSPtr data, QWidget *parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);

   setFocusPolicy(Qt::StrongFocus);

   auto con = connect(data.get(), &DataLayer::currentMatrixChanged, 
      this, [=]()
      {
         m->ui.frameView->setImageMatrix(m->data->currentMatrix(MatrixLayer::Source));
      }
   );
}

MatrixImageView::~MatrixImageView() = default;

void MatrixImageView::keyReleaseEvent(QKeyEvent* event)
{
   switch (event->key())
   {
   case Qt::Key_Up:
      return m->ui.frameView->setTranslateY(0.05);
   case Qt::Key_Down:
      return m->ui.frameView->setTranslateY(0.05);
   case Qt::Key_Left:
      return m->ui.frameView->setTranslateX(0.05);
   case Qt::Key_Right:
      return m->ui.frameView->setTranslateX(0.05);
   //case Qt::Key_PageUp:
   //case Qt::Key_PageDown:
   //   break;
   case Qt::Key_Plus:
      return m->ui.frameView->setScaleValue(0.95);
   case Qt::Key_Minus:
      return m->ui.frameView->setScaleValue(1.05);

   default:
      spdlog::debug("key press not valid: {}", event->key());
      break;
   }
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
