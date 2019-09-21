#pragma once

//class MatrixDataModel
//{
//};

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "MatrixFile.h"
#include "ImageMatrix.h"
#include "MatrixManager.h"

using MatrixFileRepository = std::vector<MatrixFileInfo>;

class MatrixDataModel final : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Name, Type, Size, Path, Extension, Count };

   explicit MatrixDataModel();
   ~MatrixDataModel() override = default;

   void setImageMatrix(const cv::Mat& matrix);

   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

private:
   QString formatFileType(MatrixFileInfo::Type type) const;

private:
   //ImageMatrix m_matrix;
   cv::Mat m_matrix;
};

using MatrixDataModelPtr = std::unique_ptr<MatrixDataModel>;

//////////////////////////////////////////////////////////////////////////////////////////

class MatrixDataProxy final : public QSortFilterProxyModel
{
public:
   explicit MatrixDataProxy(QObject* parent = nullptr);
   ~MatrixDataProxy() override = default;

   void updateSearch(const QString& searchString);
   uint getSourceIndex(const QModelIndex& index);
   MatrixFileInfo getSourceContact(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using MatrixDataProxyPtr = std::unique_ptr<MatrixDataProxy>;

// Codepage: UTF-8 (‹¸÷ˆƒ‰ﬂ)

