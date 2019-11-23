#pragma once

#include <QWidget>
#include "ui_ConfigDialog.h"

#include "ConfigEditorModel.h"
#include "DataLayer/DataLayer.h"

class ConfigDialog : public QWidget
{
    Q_OBJECT

public:
   explicit ConfigDialog(DataLayerSPtr data, QWidget *parent);
   ~ConfigDialog();

private:
   Ui::ConfigDialog ui;
   std::unique_ptr<ConfigEditorModel> m_model;
   std::unique_ptr<ConfigEditorProxy> m_proxy;
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
