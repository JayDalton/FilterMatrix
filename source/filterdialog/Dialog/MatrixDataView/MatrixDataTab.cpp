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
   m_matrixValueDataModel->setImageMatrix(matrix);
   
   auto list = m->data->currentPropertyList();
   m_matrixPropertyModel->setPropertyList(list);
}

void MatrixDataTab::setupUIElements()
{
   m_matrixValueDataModel = std::make_unique<MatrixValueDataModel>();
   m_matrixValueDataProxy = std::make_unique<MatrixValueDataProxy>();
   m_matrixValueDataProxy->setSourceModel(m_matrixValueDataModel.get());
   m->ui.treeView->setModel(m_matrixValueDataProxy.get());

   m_matrixPropertyModel = std::make_unique<MatrixPropertyModel>();
   m_matrixPropertyProxy = std::make_unique<MatrixPropertyProxy>();
   m_matrixPropertyProxy->setSourceModel(m_matrixPropertyModel.get());
   m->ui.treePropertyView->setModel(m_matrixPropertyProxy.get());
}

