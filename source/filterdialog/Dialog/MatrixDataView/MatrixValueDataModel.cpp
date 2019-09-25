#include <precompheader.h>

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

   emit sizeChanged(QRect{0, 0, 100, 100});
}

void MatrixValueDataModel::setSectionRange(const QRect& range)
{
   beginResetModel();
   m_range = range;
   endResetModel();
}

const QRect& MatrixValueDataModel::getSectionRange() const
{
   return m_range;
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
      return m_range.height();
   }
   return 0;
}

int MatrixValueDataModel::columnCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_range.width();
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

   return section;
}

QVariant MatrixValueDataModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (index.parent().isValid() 
      || (index.row() > m_range.height()) 
      || (index.column() > m_range.width()))
   {
      return {};
   }

   return m_matrix.at<float>(m_range.y() + index.row(), m_range.x() + index.column());
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


// Codepage: UTF-8 (ÜüÖöÄäẞß)
