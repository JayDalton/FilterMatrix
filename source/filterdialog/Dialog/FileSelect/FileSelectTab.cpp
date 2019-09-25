#include <precompheader.h>

#include "FileSelectTab.h"

#include "ui_FileSelectTab.h"

#include <QMenu>
#include <QtGui/qevent.h>
#include <QPushButton>
#include <QAbstractItemView>
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

   m->ui.treeView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
   m->ui.treeView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
   
   m_fileSelectModel = std::make_unique<FileSelectModel>();
   m_fileSelectProxy = std::make_unique<FileSelectProxy>();
   m_fileSelectProxy->setSourceModel(m_fileSelectModel.get());
   m->ui.treeView->setModel(m_fileSelectProxy.get());

   //m->ui.treeView.chan

   //auto con3 = connect(m->ui.treeView, &QTreeView::dataChanged, this, []() {});
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
   QFileDialog dialog{ this };
   dialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
   dialog.setNameFilter(tr("Portable Graymap (*.pgm)"));
   dialog.setViewMode(QFileDialog::Detail);

   QStringList fileNames;
   if (dialog.exec())
   {
      fileNames = dialog.selectedFiles();
      const auto filePathList{ fileNames.toVector() };

      StringVector fileList(fileNames.size());
      std::transform(filePathList.cbegin(), filePathList.cend(), fileList.begin(), 
         [](const QString& path) { return path.toStdString(); }
      );

      if (m->data->readMatrixFileInfo(fileList))
      {
         const auto repo{ m->data->getFileRepository() };
         m_fileSelectModel->reloadFileModel(repo);
         if (!repo.empty())
         {
            m->ui.treeView->setCurrentIndex(QModelIndex());
         }
      }
   }
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

// Codepage: UTF-8 (ÜüÖöÄäẞß)
