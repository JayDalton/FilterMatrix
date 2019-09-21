#include <pch.h>

#include "MatrixDataTab.h"

#include "ui_MatrixDataTab.h"

struct MatrixDataTab::Impl
{
   explicit Impl(MatrixDataTab* parent, DataLayerSPtr data) 
      : parent(parent), data(data) {}
   
   DataLayerSPtr data{ nullptr };
   Ui::MatrixDataTab ui;

private:
   MatrixDataTab* parent{ nullptr };
};

MatrixDataTab::MatrixDataTab(DataLayerSPtr data, QWidget *parent)
    : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);
   
   setupUIElements();
}


MatrixDataTab::~MatrixDataTab() = default;

void MatrixDataTab::load()
{
   auto matrix = m->data->currentMatrix();
   m_matrixDataModel->setImageMatrix(matrix);
}

void MatrixDataTab::setupUIElements()
{
   m_matrixDataModel = std::make_unique<MatrixDataModel>();
   m_matrixDataProxy = std::make_unique<MatrixDataProxy>();
   m_matrixDataProxy->setSourceModel(m_matrixDataModel.get());
   m->ui.treeView->setModel(m_matrixDataProxy.get());
}

