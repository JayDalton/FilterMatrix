#pragma once

#include "DataLayer/DataLayer.h"

#include <QWidget>

class MatrixImageView : public QWidget
{
    Q_OBJECT

public:
    explicit MatrixImageView(DataLayerSPtr data, QWidget* parent);
    ~MatrixImageView();

protected:
   //void keyPressEvent(QKeyEvent* event) override
   void keyReleaseEvent(QKeyEvent* event) override;

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
