#include <pch.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

#include "FileSelect/FileSelectTab.h"


struct FilterDialog::Impl
{
   Impl(FilterDialog* parent) : m_parent(parent) {}

   FileSelectTab* tabFileSelect{ nullptr };

   Ui::FilterDialogClass ui;

private:
   FilterDialog* m_parent{ nullptr };
};

FilterDialog::FilterDialog()
   : m{ std::make_unique<Impl>(this) }
{
   m->ui.setupUi(this);

   restoreSettings();
   setupDataLayers();
   setupTabWidgets();
}

FilterDialog::~FilterDialog() = default;

void FilterDialog::restoreSettings()
{

}

void FilterDialog::setupDataLayers()
{

}

void FilterDialog::setupTabWidgets()
{
   m->tabFileSelect = new FileSelectTab{ this };
   m->ui.tabWidget->addTab(m->tabFileSelect, "File Select");

}

