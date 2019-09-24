#include <pch.h>

#include "MatrixDataPlot.h"

#include "QCustomPlot/qcustomplot.h"

#include "ui_MatrixDataPlot.h"

struct MatrixDataPlot::Impl
{
   explicit Impl(MatrixDataPlot* parent, DataLayerSPtr data) 
      : parent(parent), data(data) {}

   DataLayerSPtr data{ nullptr };
   Ui::MatrixDataPlot ui;

private:
   MatrixDataPlot* parent{ nullptr };
};

///////////////////////////////////

MatrixDataPlot::MatrixDataPlot(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
    m->ui.setupUi(this);

    setupUIElements();
}

MatrixDataPlot::~MatrixDataPlot() = default;

void MatrixDataPlot::setupUIElements()
{
   // generate some data:
   QVector<double> x(101), y(101); // initialize with entries 0..100
   for (int i=0; i<101; ++i)
   {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i];  // let's plot a quadratic function
   }

   // create graph and assign data to it:
   m->ui.customPlot->addGraph();
   m->ui.customPlot->graph(0)->setData(x, y);

   // give the axes some labels:
   m->ui.customPlot->xAxis->setLabel("x");
   m->ui.customPlot->yAxis->setLabel("y");

   // set axes ranges, so we see all data:
   m->ui.customPlot->xAxis->setRange(-1, 1);
   m->ui.customPlot->yAxis->setRange(0, 1);
}

