#include "ConfigDialog.h"

#include <DataLayer\DataLayer.h>

ConfigDialog::ConfigDialog(DataLayerSPtr data, QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_model = std::make_unique<ConfigEditorModel>();
    m_proxy = std::make_unique<ConfigEditorProxy>();

    ui.treeView->setUniformRowHeights(true);
    ui.treeView->setModel(m_model.get());
}

ConfigDialog::~ConfigDialog() = default;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
