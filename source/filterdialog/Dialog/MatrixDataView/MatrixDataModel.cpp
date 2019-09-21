#include <pch.h>

#include "MatrixDataModel.h"

#include <opencv2/core/mat.hpp>

MatrixDataModel::MatrixDataModel()
{

}

void MatrixDataModel::setImageMatrix(const cv::Mat& matrix)
{
   beginResetModel();
   m_matrix = matrix;
   endResetModel();
}

QModelIndex MatrixDataModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return createIndex(row, column);
   }
   return {};
}

QModelIndex MatrixDataModel::parent(const QModelIndex& child) const
{
   return {};
}

int MatrixDataModel::rowCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_matrix.rows; //static_cast<int>(m_matrix.size());
   }
   return 0;
}

int MatrixDataModel::columnCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_matrix.cols;// static_cast<int>(Column::Count);
   }
   return 0;
}

Qt::ItemFlags MatrixDataModel::flags(const QModelIndex& index) const
{
   return QAbstractItemModel::flags(index);
}

QVariant MatrixDataModel::headerData(int section, Qt::Orientation orientation, int role) const
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

QVariant MatrixDataModel::data(const QModelIndex& index, int role) const
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

   auto row = index.row();
   auto col = index.column();
   auto size = m_matrix.size;
   auto dims = m_matrix.dims;
   auto type = m_matrix.type();
   auto chans = m_matrix.channels();

   //auto val = m_matrix.at<double>(index.row(), index.column());

   return 0;// m_matrix.at<double>(index.row(), index.column());
}

QString MatrixDataModel::formatFileType(MatrixFileInfo::Type type) const
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

MatrixDataProxy::MatrixDataProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

void MatrixDataProxy::updateSearch(const QString& searchString)
{
   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
   invalidate();
}

uint MatrixDataProxy::getSourceIndex(const QModelIndex& index)
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

bool MatrixDataProxy::filterAcceptsRow(int row, const QModelIndex& parent) const
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

bool MatrixDataProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)
