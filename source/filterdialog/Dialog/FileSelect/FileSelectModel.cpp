#include <pch.h>

#include "FileSelectModel.h"

struct FileInfoCompare
{
   bool operator()(const MatrixFileInfo& lhs, const MatrixFileInfo& rhs) 
   {
      return lhs.getPath() == rhs.getPath();
   }
};

FileSelectModel::FileSelectModel()
{

}

void FileSelectModel::setImageMatrix(MatrixFileInfo matrixFile)
{
   beginResetModel();
   m_repository.push_back(matrixFile);
   endResetModel();
}

void FileSelectModel::reloadFileModel(const MatrixFileRepository& repository)
{
   beginResetModel();
   m_repository.assign(repository.cbegin(), repository.cend());
   auto last = std::unique(m_repository.begin(), m_repository.end(), FileInfoCompare{});
   m_repository.erase(last, m_repository.end()); 
   endResetModel();
}

MatrixFileInfo FileSelectModel::getMatrixFile(const QModelIndex& index) const
{
   return m_repository.at(index.row());
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
      return static_cast<int>(m_repository.size());
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
      return "Dateiname";
   case Column::Path:
      return "Verzeichnis";
   case Column::Size:
      return "Bytes";
   case Column::Type:
      return "Typ";
   case Column::Extension:
      return "Dateiendung";
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
      (index.row() >= m_repository.size()) ||
      (index.column() > static_cast<int>(Column::Count)))
   {
      return {};
   }

   const auto entry{ m_repository.at(index.row()) };
   switch (static_cast<Column>(index.column()))
   {
   case Column::Name: 
      return entry.getFileName().data();
   case Column::Path:
      return entry.getFilePath().data();
   case Column::Type:
      return formatFileType(entry.getFileType());
   case Column::Size:
      return entry.getFileSize();
   case Column::Extension:
      return entry.getExtension().data();
   default: 
      return {};
   }
}

QString FileSelectModel::formatFileType(MatrixFileInfo::Type type) const
{
   switch (type)
   {
   case MatrixFileInfo::Type::None:
      return "none";
   case MatrixFileInfo::Type::Graymap:
      return "Graymap";
   default:
      return "undefined";
   }
}

//////////////////////////////////////////////////////////////////////////////////////////

FileSelectProxy::FileSelectProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

void FileSelectProxy::updateSearch(const QString& searchString)
{
   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
   invalidate();
}

uint FileSelectProxy::getSourceIndex(const QModelIndex& index)
{
   auto sourceIndex{ mapToSource(index) };
   auto sourceRow{ sourceIndex.row() };
   return static_cast<uint>(sourceRow);
}

MatrixFileInfo FileSelectProxy::getSourceContact(const QModelIndex& index)
{
   const auto sourceIndex{ mapFromSource(index) };
   if (auto model = qobject_cast<FileSelectModel*>(sourceModel()))
   {
      return model->getMatrixFile(sourceIndex);
   }
   return MatrixFileInfo{""};
}

bool FileSelectProxy::filterAcceptsRow(int row, const QModelIndex& parent) const
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

bool FileSelectProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)
