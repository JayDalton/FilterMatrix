#pragma once

#include <QWidget>

class FileSelectTab : public QWidget
{
    Q_OBJECT

public:
    ~FileSelectTab() = default;
    explicit FileSelectTab(QWidget* parent);

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
