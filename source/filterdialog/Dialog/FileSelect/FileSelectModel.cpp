#include <pch.h>

#include "FileSelectModel.h"

void FileSelectModel::addMatrixFile(MatrixFile matrixFile)
{
}

MatrixFile FileSelectModel::getMatrixFile(const QModelIndex& index) const
{
   return MatrixFile{""};
}

QModelIndex FileSelectModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return createIndex(row, column);
   }
   return {};
}

QModelIndex FileSelectModel::parent(const QModelIndex& child) const
{
   return {};
}

int FileSelectModel::rowCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return static_cast<int>(m_repo.size());
   }
   return 0;
}

int FileSelectModel::columnCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return static_cast<int>(Column::Count);
   }
   return 0;
}

Qt::ItemFlags FileSelectModel::flags(const QModelIndex& index) const
{
   return QAbstractItemModel::flags(index);
}

QVariant FileSelectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   switch (static_cast<Column>(section))
   {
   case Column::Name:
      return "Vorname";
   case Column::Path:
      return "Nachname";
   case Column::Size:
      return "Firma";
   case Column::Type:
      return "Art";
   case Column::Extension:
      return "Telefonnummer";
   default:
      return {};
   }
}

QVariant FileSelectModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (index.parent().isValid() || 
      (index.row() >= m_repo.size()) ||
      (index.column() > static_cast<int>(Column::Count)))
   {
      return {};
   }

   const auto entry{ m_repo.at(index.row()) };
   switch (static_cast<Column>(index.column()))
   {
   case Column::Name: 
      return QVariant{ entry.m_fileName.data() };
   case Column::Path:
      return QVariant{ entry.m_filePath.data() };
   //case Column::Size:
   //   return QVariant{ entry.m_fileSize.data() };
   //case Column::Type:
   //   return QVariant{ entry.m_fileType.data() };
   case Column::Extension:
      return QVariant{ entry.m_extension.data() };
   default: 
      return {};
   }
}

//////////////////////////////////////////////////////////////////////////////////////////

FileSelectSortFilterProxyModel::FileSelectSortFilterProxyModel(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

void FileSelectSortFilterProxyModel::updateSearch(const QString& searchString)
{
   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
   invalidate();
}

uint FileSelectSortFilterProxyModel::getSourceIndex(const QModelIndex& index)
{
   auto sourceIndex{ mapToSource(index) };
   auto sourceRow{ sourceIndex.row() };
   return static_cast<uint>(sourceRow);
}

MatrixFile FileSelectSortFilterProxyModel::getSourceContact(const QModelIndex& index)
{
   const auto sourceIndex{ mapFromSource(index) };
   if (auto model = qobject_cast<FileSelectModel*>(sourceModel()))
   {
      return model->getMatrixFile(sourceIndex);
   }
   return MatrixFile{""};
}

bool FileSelectSortFilterProxyModel::filterAcceptsRow(int row, const QModelIndex& parent) const
{
   // leeres Suchwort = alles anzeigen
   if (m_searchStringList.isEmpty())
   {
      return true;
   }

   const auto model{ sourceModel() };
   for (const auto& searchString : m_searchStringList)
   {
      bool searchStringFound{ false };
      for (auto column{ 0 }; column < model->columnCount(); ++column)
      {
         QModelIndex levelOneIndex = model->index(row, column, parent);
         QString stringData = levelOneIndex.data().toString();
         if (stringData.contains(searchString, Qt::CaseInsensitive))
         {
            searchStringFound = true;
            break;
         }
      }

      if (searchStringFound)
      {
         continue;
      }

      return false;
   }

   return true;
}

bool FileSelectSortFilterProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)
