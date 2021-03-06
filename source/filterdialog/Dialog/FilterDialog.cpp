﻿#include <precompheader.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

#include "QTabWidget"

#include "FileSelect/FileSelectTab.h"
#include "MatrixDataView/MatrixDataTab.h"
#include "MatrixDataPlot/MatrixDataPlot.h"
#include "MatrixImageView/MatrixImageView.h"
#include "Dialog/EditConfig/ConfigDialog.h"

#include "DataLayer/DataLayer.h"

struct FilterDialog::Impl
{
   explicit Impl(DataLayerSPtr data) : data(data) {}

   ConfigDialog* tabConfigDialog{ nullptr };
   FileSelectTab* tabFileSelect{ nullptr };
   MatrixDataTab* tabMatrixData{ nullptr };
   MatrixDataPlot* tabMatrixPlot{ nullptr };
   MatrixImageView* tabMatrixView{ nullptr };

   DataLayerSPtr data{ nullptr };

   Ui::FilterDialogClass ui;

private:
};

//////////////////////////////////////////////////////////////////

FilterDialog::FilterDialog(DataLayerSPtr data)
   : m{ std::make_unique<Impl>(data) }
{
   m->ui.setupUi(this);

   setWindowTitle(tr("Matrix Filter Dialog"));

   restoreSettings();
   setupDataLayers();
   setupTabWidgets();
}

FilterDialog::~FilterDialog() = default;
//FilterDialog::FilterDialog(FilterDialog&& rhs) = default;
//FilterDialog& FilterDialog::operator=(FilterDialog&&) = default;

void FilterDialog::closeEvent(QCloseEvent* event)
{
   auto config = m->data->settings();
   config.setValue("geometry", saveGeometry());
   QWidget::closeEvent(event);
}

void FilterDialog::restoreSettings()
{
   const auto settings = m->data->settings();
   restoreGeometry(settings.value("geometry").toByteArray());
}

void FilterDialog::saveSettings()
{
}

void FilterDialog::setupDataLayers()
{
   //m->data->loadConfiguration();
}

void FilterDialog::setupTabWidgets()
{
   m->tabFileSelect = new FileSelectTab{ m->data, this };
   m->ui.tabWidget->addTab(m->tabFileSelect, "File Select");

   m->tabConfigDialog = new ConfigDialog{ m->data, this };
   m->ui.tabWidget->addTab(m->tabConfigDialog, "Config File");

   m->tabMatrixView = new MatrixImageView{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixView, "Matrix View");

   m->tabMatrixData = new MatrixDataTab{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixData, "Matrix Data");

   m->tabMatrixPlot = new MatrixDataPlot{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixPlot, "Matrix Plot");

   auto con = connect(m->tabFileSelect, &FileSelectTab::displayMatrixData, 
      this, [=]() { m->ui.tabWidget->setCurrentWidget(m->tabMatrixView); }
   );
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
