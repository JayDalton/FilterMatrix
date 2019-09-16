#include <pch.h>

#include "FileSelectTab.h"

#include "ui_FileSelectTab.h"

struct FileSelectTab::Impl
{
   explicit Impl(FileSelectTab* parent) : m_parent{parent} {}

   Ui::FileSelectTab ui;

private:
   FileSelectTab* m_parent{ nullptr };
};

FileSelectTab::FileSelectTab(QWidget* parent)
    : QWidget(parent), m(std::make_unique<Impl>(this))
{
    m->ui.setupUi(this);

}

