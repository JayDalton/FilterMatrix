#include "precompheader.h"

#include "MatrixImageView.h"

#include "ui_MatrixImageView.h"

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
}

MatrixImageView::~MatrixImageView() = default;


// Codepage: UTF-8 (ÜüÖöÄäẞß)
