#include "FilterDialog.h"

#include <QtGui/qevent.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>

struct FilterDialog::Impl
{
   explicit Impl(FilterDialog* parent) 
      : m_parent(parent) {}


private:
   FilterDialog* m_parent;
};

// ############################################################################################

FilterDialog::FilterDialog()
    : m(std::make_unique<Impl>(this))
{
   ui.setupUi(this);

   setupActions();
   setupMenus();

   QString message = tr("A context menu is available by right-clicking");
   ui.statusBar->showMessage(message);
   
   setWindowTitle(tr("Menus"));
}

FilterDialog::~FilterDialog() = default;

void FilterDialog::setupActions()
{
   m_openFile = std::make_unique<QAction>(tr("&Öffnen"));
   m_openFile->setShortcuts(QKeySequence::Open);
   m_openFile->setStatusTip(tr("Create a new file"));
   connect(m_openFile.get(), &QAction::triggered, this, &FilterDialog::openFile);

   m_saveFile = std::make_unique<QAction>(tr("&Sichern"));
   m_saveFile->setShortcuts(QKeySequence::Save);
   m_saveFile->setStatusTip(tr("Save existing file"));
   connect(m_saveFile.get(), &QAction::triggered, this, &FilterDialog::saveFile);
}

void FilterDialog::setupMenus()
{
   auto fileMenu{ menuBar()->addMenu(tr("Datei")) };

}

void FilterDialog::openFile()
{
   QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open Address Book"), "",
      tr("Address Book (*.abk);;All Files (*)"));

   if (fileName.isEmpty())
      return;
   else {

      QFile file(fileName);

      if (!file.open(QIODevice::ReadOnly)) {
         QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
         return;
      }

      //QDataStream in(&file);
      //in.setVersion(QDataStream::Qt_4_5);
      //contacts.clear();   // clear existing contacts
      //in >> contacts;

      //if (contacts.isEmpty()) {
      //   QMessageBox::information(this, tr("No contacts in file"),
      //      tr("The file you are attempting to open contains no contacts."));
      //} else {
      //   QMap<QString, QString>::iterator i = contacts.begin();
      //   nameLine->setText(i.key());
      //   addressText->setText(i.value());
      //}
   }

   //updateInterface(NavigationMode);
}

void FilterDialog::saveFile()
{
}

void FilterDialog::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu menu(this);
   menu.addAction(m_openFile.get());
   menu.addAction(m_saveFile.get());
   menu.exec(event->globalPos());
}

