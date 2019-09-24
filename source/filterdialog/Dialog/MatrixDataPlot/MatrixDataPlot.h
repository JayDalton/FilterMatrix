#pragma once

#include <QWidget>

#include "DataLayer/DataLayer.h"

class MatrixDataPlot : public QWidget
{
    Q_OBJECT

public:
   explicit MatrixDataPlot(DataLayerSPtr data, QWidget* parent);
   ~MatrixDataPlot();

private:
   void setupUIElements();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
