#pragma once

#include <QWidget>

#include "DataLayer/DataLayer.h"

class MatrixDataPlot : public QWidget
{
    Q_OBJECT

public:
   explicit MatrixDataPlot(DataLayerSPtr data, QWidget* parent);
   ~MatrixDataPlot();

   void load(int index);

private:
   void plotGraph(const std::vector<double>& values);

private:
   void setupUIElements();
   void setupSpinBox(int size);

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
