#include "MatrixPropertyModel.h"

MatrixPropertyModel::MatrixPropertyModel()
{

}

void MatrixPropertyModel::setPropertyList(const MatrixPropertyList& list)
{
   beginResetModel();
   m_list = list;
   endResetModel();
}

QModelIndex MatrixPropertyModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return createIndex(row, column);
   }
   return {};
}

QModelIndex MatrixPropertyModel::parent(const QModelIndex& child) const
{
   return {};
}

int MatrixPropertyModel::rowCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_list.size();
   }
   return 0;
}

int MatrixPropertyModel::columnCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return static_cast<int>(Column::Count);
   }
   return 0;
}

Qt::ItemFlags MatrixPropertyModel::flags(const QModelIndex& index) const
{
   return QAbstractItemModel::flags(index);
}

QVariant MatrixPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   switch (static_cast<Column>(section))
   {
   case Column::Label:
      return "Bezeinchner";
   case Column::Value:
      return "Werte";
   default:
      return {};
   }
   return {};
}

QVariant MatrixPropertyModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (index.parent().isValid() || 
      (index.row() > m_list.size()) ||
      (index.column() > static_cast<int>(Column::Count)))
   {
      return {};
   }

   const auto& property{ m_list.at(index.row()) };

   switch (index.column())
   {
   case 0: // Label
      return QString::fromStdString(property.m_label);
   case 1: // Value
      //return property.m_value;
   default:
      return {};
   }

   //return /*index.column() ? property.m_value : */QString::fromStdString(property.m_label);
}

QString MatrixPropertyModel::formatFileType(MatrixFileInfo::Type type) const
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

MatrixPropertyProxy::MatrixPropertyProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

void MatrixPropertyProxy::updateSearch(const QString& searchString)
{
   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
   invalidate();
}

uint MatrixPropertyProxy::getSourceIndex(const QModelIndex& index)
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

bool MatrixPropertyProxy::filterAcceptsRow(int row, const QModelIndex& parent) const
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

bool MatrixPropertyProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)
