#pragma once

#include <QIcon>
#include <QColor>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

struct SingleValueItem
{
   QString m_label{};
   QColor m_color{ Qt::black };// ForegroundRole
   QIcon m_icon{};//DecorationRole
   bool m_isBold{ false };//FontRole
};

struct ServerInfoItem 
{
   using ServerInfoItemPtr = std::unique_ptr<ServerInfoItem>;

   ServerInfoItem(ServerInfoItem* parent = nullptr);
   ServerInfoItem(ServerInfoItem* parent, SingleValueItem value);
   //TreeItem(TreeItem* parent, const ValueItem& value);
   ~ServerInfoItem() = default;

   ServerInfoItem* appendChild(ServerInfoItemPtr item);

   int row() const;
   int childCount() const;

   ServerInfoItem* getParent() const;
   ServerInfoItem* getChild(int row) const;
   const SingleValueItem& data(int column) const;

   void logItemRecursive(int padding = 0) const;

private:
   int indexOf(const ServerInfoItem* item) const;

private:
   SingleValueItem m_value;
   ServerInfoItem* m_parent{ nullptr };
   std::vector<ServerInfoItemPtr> m_childs;
};

using ServerInfoItemPtr = std::unique_ptr<ServerInfoItem>;

class ConfigEditorModel : public QAbstractItemModel
{
   Q_OBJECT

public:
   ConfigEditorModel();
   //~ConfigEditorModel() = default;

   void updateModel();

   int rowCount(const QModelIndex &parent = {}) const override;
   Qt::ItemFlags flags(const QModelIndex &index) const override;
   int columnCount(const QModelIndex &parent = {}) const override;
   QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
   QModelIndex parent(const QModelIndex &index) const override;
   QVariant data(const QModelIndex &index, int role) const override;

private:
   std::unique_ptr<ServerInfoItem> m_rootItem;
};

struct ConfigEditorProxy : public QSortFilterProxyModel
{
   ConfigEditorProxy();
   ~ConfigEditorProxy() = default;

protected:
   bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
   bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
