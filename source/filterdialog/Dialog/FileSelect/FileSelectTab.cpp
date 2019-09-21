#include <pch.h>

#include "FileSelectTab.h"

#include "ui_FileSelectTab.h"

#include <QMenu>
#include <QtGui/qevent.h>
#include <QPushButton>
#include <QtWidgets\qfiledialog.h>
#include <QtWidgets\qmessagebox.h>
#include <FileManager.h>

struct FileSelectTab::Impl
{
   explicit Impl(FileSelectTab* parent, DataLayerSPtr data) 
      : m_parent{ parent }, data{data} {}

   std::unique_ptr<QAction> m_openFile{nullptr};
   std::unique_ptr<QAction> m_saveFile{nullptr};

   DataLayerSPtr data{ nullptr };
   Ui::FileSelectTab ui;

private:
   FileSelectTab* m_parent{ nullptr };
};

//////////////////////////////////////////////////////////////////////

FileSelectTab::FileSelectTab(DataLayerSPtr data, QWidget* parent)
    : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);

   setupUIElements();
   setupActions();
   setupMenus();
}

void FileSelectTab::setupUIElements()
{
   auto con1 = connect(m->ui.openButton, &QPushButton::clicked, this, [&]() { openFile(); });
   auto con2 = connect(m->ui.loadButton, &QPushButton::clicked, this, [&]() { loadFile(); });

   m_fileSelectModel = std::make_unique<FileSelectModel>();
   m_fileSelectProxy = std::make_unique<FileSelectProxy>();
   m_fileSelectProxy->setSourceModel(m_fileSelectModel.get());
   m->ui.treeView->setModel(m_fileSelectProxy.get());
}

void FileSelectTab::setupActions()
{
   m->m_openFile = std::make_unique<QAction>(tr("&Öffnen"));
   m->m_openFile->setShortcuts(QKeySequence::Open);
   m->m_openFile->setStatusTip(tr("Create a new file"));
   connect(m->m_openFile.get(), &QAction::triggered, this, &FileSelectTab::openFile);

   m->m_saveFile = std::make_unique<QAction>(tr("&Sichern"));
   m->m_saveFile->setShortcuts(QKeySequence::Save);
   m->m_saveFile->setStatusTip(tr("Save existing file"));
   connect(m->m_saveFile.get(), &QAction::triggered, this, &FileSelectTab::saveFile);
}

void FileSelectTab::setupMenus()
{
   //auto fileMenu{ menuBar()->addMenu(tr("Datei")) };

}

void FileSelectTab::openFile()
{
   QString fileName{ QFileDialog::getOpenFileName(
      this, tr("Open Matrix File"), "",
      tr("Portable Graymap (*.pgm);;All Files (*)")) };

   if (fileName.isEmpty())
   {
      return;
   }

   if (auto file = m->data->openMatrixFile(fileName.toStdString()))
   {
      m_fileSelectModel->setImageMatrix(file.value());
      return;
   }

   QMessageBox::information(this, tr("Unable to open file"), fileName);
}

void FileSelectTab::loadFile()
{
   auto* selectionModel = m->ui.treeView->selectionModel();
   if (!selectionModel->hasSelection())
   {
      return;
   }

   auto index = selectionModel->currentIndex();
   auto file = m_fileSelectModel->getMatrixFile(index);
   m->data->loadMatrixFile(file);

   emit displayMatrixData();

   // switch dialog tab with file index
}

void FileSelectTab::saveFile()
{
}

void FileSelectTab::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu menu(this);
   menu.addAction(m->m_openFile.get());
   menu.addAction(m->m_saveFile.get());
   menu.exec(event->globalPos());
}
