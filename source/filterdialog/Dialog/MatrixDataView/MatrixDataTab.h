#pragma once

#include <QWidget>

#include "DataLayer/DataLayer.h"
#include "MatrixDataModel.h"

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

   MatrixDataModelPtr m_matrixDataModel{ nullptr };
   MatrixDataProxyPtr m_matrixDataProxy{ nullptr };
};
