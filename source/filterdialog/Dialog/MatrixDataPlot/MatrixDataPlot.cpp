#include <precompheader.h>

#include "MatrixDataPlot.h"

#include <QSpinBox>
#include <QPushButton>
#include "QCustomPlot/qcustomplot.h"

#include "ui_MatrixDataPlot.h"

struct MatrixDataPlot::Impl
{
   explicit Impl(MatrixDataPlot* parent, DataLayerSPtr data) 
      : parent(parent), data(data) {}

   DataLayerSPtr data{ nullptr };
   Ui::MatrixDataPlot ui;

   int index{ 0 };

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

void MatrixDataPlot::load(int index)
{
   const auto matrix = m->data->currentMatrix();

   m->ui.customPlot->clearGraphs();

   if (index > matrix.rows)
   {
      return;
   }

   const auto row = matrix.row(index);
   std::vector<double> values(row.begin<float>(), row.end<float>());

   setupSpinBox(values.size());

   plotGraph(values);
}

void MatrixDataPlot::plotGraph(const std::vector<double>& values)
{
   const auto y{ QVector<double>::fromStdVector(values) };

   QVector<double> x(values.size());
   std::iota(x.begin(), x.end(), 0);

   // give the axes some labels:
   m->ui.customPlot->xAxis->setLabel("x");
   m->ui.customPlot->yAxis->setLabel("y");

   m->ui.customPlot->addGraph();

   QPen pen;
   pen.setColor(QColor(255, 200, 20, 200));
   m->ui.customPlot->graph(0)->setPen(pen);
   m->ui.customPlot->graph(0)->setBrush(QBrush(QColor(255,200,20,70)));
   
   m->ui.customPlot->graph(0)->setData(x, y);
   m->ui.customPlot->graph(0)->rescaleAxes();

   // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
   m->ui.customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom /*| QCP::iSelectPlottables*/);

   m->ui.customPlot->replot();
}

void MatrixDataPlot::setupUIElements()
{
   auto con1 = connect(m->ui.layerBox, QOverload<int>::of(&QSpinBox::valueChanged),
      this, [&](int value) { load(value); }
   );

   setupSpinBox(0);
}

void MatrixDataPlot::setupSpinBox(int size)
{
   m->ui.layerBox->setMinimum(0);
   m->ui.layerBox->setMaximum(size);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
