#include <pch.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

#include "FileSelect/FileSelectTab.h"

#include "DataLayer/DataLayer.h"

struct FilterDialog::Impl
{
   Impl(FilterDialog* parent) : m_parent(parent) {}

   FileSelectTab* tabFileSelect{ nullptr };

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

}

