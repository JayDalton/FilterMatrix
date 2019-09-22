#pragma once

#include <QWidget>

#include "DataLayer/DataLayer.h"
#include "MatrixValueDataModel.h"
#include "MatrixPropertyModel.h"

class MatrixDataTab : public QWidget
{
    Q_OBJECT

public:
    MatrixDataTab(DataLayerSPtr data, QWidget *parent = nullptr);
    ~MatrixDataTab();

    void load();

private:
   void setupUIElements();

private:
   struct Impl;
   std::unique_ptr<Impl> m;

   MatrixValueDataModelPtr m_matrixDataModel{ nullptr };
   MatrixValueDataProxyPtr m_matrixDataProxy{ nullptr };
};
