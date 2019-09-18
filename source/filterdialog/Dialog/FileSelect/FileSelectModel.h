#pragma once

#include "qabstractitemmodel.h"

#include "MatrixFile.h"

class FileSelectModel final : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Name, Path, Size, Type, Count };

   explicit FileSelectModel();
   ~FileSelectModel() override = default;

   //void addMatrixFile();
   //TelUnifyContact getContactEntry(const QModelIndex& index) const;

   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

private:
   //TelUnifyContactEntriesSPtr m_contacts{};
};

