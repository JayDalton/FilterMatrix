#pragma once

#include <QSize>
#include <QRect>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "MatrixFile.h"
#include "ImageMatrix.h"
#include "MatrixManager.h"

using MatrixFileRepository = std::vector<MatrixFileInfo>;

class MatrixValueDataModel final : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Name, Type, Size, Path, Extension, Count };

   explicit MatrixValueDataModel();
   ~MatrixValueDataModel() override = default;

   void setImageMatrix(const cv::Mat& matrix);
   void setSectionRange(const QRect& range);
   const QRect& getSectionRange() const;

signals:
   void sizeChanged(QRect size);

protected:
   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

private:

private:
   QRect m_range;// {0, 0, 100, 100};
   //ImageMatrix m_matrix;
   cv::Mat m_matrix;
};

using MatrixValueDataModelPtr = std::unique_ptr<MatrixValueDataModel>;

//////////////////////////////////////////////////////////////////////////////////////////

class MatrixValueDataProxy final : public QSortFilterProxyModel
{
public:
   explicit MatrixValueDataProxy(QObject* parent = nullptr);
   ~MatrixValueDataProxy() override = default;

   void updateSearch(const QString& searchString);
   uint getSourceIndex(const QModelIndex& index);
   MatrixFileInfo getSourceContact(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using MatrixValueDataProxyPtr = std::unique_ptr<MatrixValueDataProxy>;

// Codepage: UTF-8 (�������)

