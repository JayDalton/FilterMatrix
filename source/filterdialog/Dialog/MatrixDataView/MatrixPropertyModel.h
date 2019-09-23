#pragma once

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "MatrixFile.h"
#include "ImageMatrix.h"
#include "MatrixManager.h"

class MatrixPropertyModel final : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Label, Value, Count };

   explicit MatrixPropertyModel();
   ~MatrixPropertyModel() override = default;

   void setPropertyList(const MatrixPropertyList& list);

   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

private:
   QString formatMatrixProperty(const MatrixProperty& property) const;

private:
   MatrixPropertyList m_list;
};

using MatrixPropertyModelPtr = std::unique_ptr<MatrixPropertyModel>;

//////////////////////////////////////////////////////////////////////////////////////////

class MatrixPropertyProxy final : public QSortFilterProxyModel
{
public:
   explicit MatrixPropertyProxy(QObject* parent = nullptr);
   ~MatrixPropertyProxy() override = default;

   void updateSearch(const QString& searchString);
   uint getSourceIndex(const QModelIndex& index);
   MatrixFileInfo getSourceContact(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using MatrixPropertyProxyPtr = std::unique_ptr<MatrixPropertyProxy>;
