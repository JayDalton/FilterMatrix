#include <pch.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

#include "QTabWidget"

#include "FileSelect/FileSelectTab.h"
#include "MatrixDataView/MatrixDataTab.h"
#include "MatrixDataPlot/MatrixDataPlot.h"

#include "DataLayer/DataLayer.h"

struct FilterDialog::Impl
{
   Impl(FilterDialog* parent) : m_parent(parent) {}

   FileSelectTab* tabFileSelect{ nullptr };
   MatrixDataTab* tabMatrixData{ nullptr };
   MatrixDataPlot* tabMatrixPlot{ nullptr };

   DataLayerSPtr data{ nullptr };

   Ui::FilterDialogClass ui;

private:
   FilterDialog* m_parent{ nullptr };
};

//////////////////////////////////////////////////////////////////

FilterDialog::FilterDialog()
   : m{ std::make_unique<Impl>(this) }
{
   m->ui.setupUi(this);

   setWindowTitle(tr("Matrix Filter Dialog"));

   restoreSettings();
   setupDataLayers();
   setupTabWidgets();
}

FilterDialog::~FilterDialog() = default;

void FilterDialog::closeEvent(QCloseEvent* event)
{
   saveSettings();
}

void FilterDialog::restoreSettings()
{

}

void FilterDialog::saveSettings()
{
}

void FilterDialog::setupDataLayers()
{
   m->data = std::make_shared<DataLayer>();
   m->data->loadConfiguration();
}

void FilterDialog::setupTabWidgets()
{
   m->tabFileSelect = new FileSelectTab{ m->data, this };
   m->ui.tabWidget->addTab(m->tabFileSelect, "File Select");

   m->tabMatrixData = new MatrixDataTab{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixData, "Matrix Data");

   m->tabMatrixPlot = new MatrixDataPlot{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixPlot, "Matrix Plot");

   auto con1 = connect(m->tabFileSelect, &FileSelectTab::displayMatrixData, 
      this, [=]() {
         m->tabMatrixData->load();
         m->ui.tabWidget->setCurrentWidget(m->tabMatrixData);
      });

   auto con2 = connect(m->tabFileSelect, &FileSelectTab::displayMatrixData, 
      this, [=]() {
         m->tabMatrixPlot->load(0);
         m->ui.tabWidget->setCurrentWidget(m->tabMatrixData);
      });
}

