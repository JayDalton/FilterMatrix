#pragma once

#include <memory>

#include <QWidget>

#include "DataLayer/DataLayer.h"

class MatrixImageView : public QWidget
{
    Q_OBJECT

public:
    explicit MatrixImageView(DataLayerSPtr data, QWidget* parent);
    ~MatrixImageView();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
