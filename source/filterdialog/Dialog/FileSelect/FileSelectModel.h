#pragma once

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "MatrixFile.h"

using MatrixFileRepository = std::vector<MatrixFile>;

class FileSelectModel final : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Name, Path, Size, Type, Extension, Count };

   explicit FileSelectModel();
   ~FileSelectModel() override = default;

   void addMatrixFile(MatrixFile matrixFile);
   MatrixFile getMatrixFile(const QModelIndex& index) const;

   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

private:
   QString formatFileType(MatrixFile::Type type) const;

private:
   MatrixFileRepository m_repo;
   //TelUnifyContactEntriesSPtr m_contacts{};
};

using TelUnifyContactsModelPtr = std::unique_ptr<MatrixFileRepository>;

//////////////////////////////////////////////////////////////////////////////////////////

class FileSelectSortFilterProxyModel final : public QSortFilterProxyModel
{
public:
   explicit FileSelectSortFilterProxyModel(QObject* parent = nullptr);
   ~FileSelectSortFilterProxyModel() override = default;

   void updateSearch(const QString& searchString);
   uint getSourceIndex(const QModelIndex& index);
   MatrixFile getSourceContact(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using TelUnifyContactsProxyModelPtr = std::unique_ptr<FileSelectSortFilterProxyModel>;

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)
