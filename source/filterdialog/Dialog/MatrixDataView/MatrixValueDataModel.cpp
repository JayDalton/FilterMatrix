#include <pch.h>

#include "MatrixValueDataModel.h"

#include <opencv2/core/mat.hpp>

MatrixValueDataModel::MatrixValueDataModel()
{

}

void MatrixValueDataModel::setImageMatrix(const cv::Mat& matrix)
{
   beginResetModel();
   m_matrix = matrix;
   endResetModel();
}

QModelIndex MatrixValueDataModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return createIndex(row, column);
   }
   return {};
}

QModelIndex MatrixValueDataModel::parent(const QModelIndex& child) const
{
   return {};
}

int MatrixValueDataModel::rowCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_matrix.rows; //static_cast<int>(m_matrix.size());
   }
   return 0;
}

int MatrixValueDataModel::columnCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_matrix.cols;// static_cast<int>(Column::Count);
   }
   return 0;
}

Qt::ItemFlags MatrixValueDataModel::flags(const QModelIndex& index) const
{
   return QAbstractItemModel::flags(index);
}

QVariant MatrixValueDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   //switch (static_cast<Column>(section))
   //{
   //case Column::Name:
   //   return "Dateiname";
   //case Column::Path:
   //   return "Verzeichnis";
   //case Column::Size:
   //   return "Bytes";
   //case Column::Type:
   //   return "Typ";
   //case Column::Extension:
   //   return "Dateiendung";
   //default:
   //   return {};
   //}
   return {};
}

QVariant MatrixValueDataModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (index.parent().isValid() || 
      (index.row() > m_matrix.rows) ||
      (index.column() > m_matrix.cols))
   {
      return {};
   }

   return m_matrix.at<float>(index.row(), index.column());
}

QString MatrixValueDataModel::formatFileType(MatrixFileInfo::Type type) const
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

MatrixValueDataProxy::MatrixValueDataProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

void MatrixValueDataProxy::updateSearch(const QString& searchString)
{
   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
   invalidate();
}

uint MatrixValueDataProxy::getSourceIndex(const QModelIndex& index)
{
   auto sourceIndex{ mapToSource(index) };
   auto sourceRow{ sourceIndex.row() };
   return static_cast<uint>(sourceRow);
}

//MatrixFileInfo MatrixDataProxy::getSourceContact(const QModelIndex& index)
//{
//   const auto sourceIndex{ mapFromSource(index) };
//   if (auto model = qobject_cast<MatrixDataModel*>(sourceModel()))
//   {
//      return model->getMatrixFile(sourceIndex);
//   }
//   return MatrixFileInfo{""};
//}

bool MatrixValueDataProxy::filterAcceptsRow(int row, const QModelIndex& parent) const
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

bool MatrixValueDataProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)
