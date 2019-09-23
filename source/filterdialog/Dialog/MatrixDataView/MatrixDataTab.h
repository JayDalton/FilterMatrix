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
   void setupMatrixRange(const QRect& range);
   QRect retriveMatrixRange() const;

private:
   struct Impl;
   std::unique_ptr<Impl> m;

   MatrixValueDataModelPtr m_matrixValueDataModel{ nullptr };
   MatrixValueDataProxyPtr m_matrixValueDataProxy{ nullptr };

   MatrixPropertyModelPtr m_matrixPropertyModel{ nullptr };
   MatrixPropertyProxyPtr m_matrixPropertyProxy{ nullptr };
};
