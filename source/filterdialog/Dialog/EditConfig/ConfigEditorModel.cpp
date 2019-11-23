#include "precompheader.h"

#include "ConfigEditorModel.h"

#include "Logger/Logger.h"

//////////////////////////////////////////////////////////////////////////////////////////

ServerInfoItem::ServerInfoItem(ServerInfoItem* parent)
   : m_parent(parent)
{
}

ServerInfoItem::ServerInfoItem(ServerInfoItem* parent, SingleValueItem value)
   : m_parent(parent), m_value(std::move(value))
{
}

//TreeItem::TreeItem(TreeItem* parent, const ValueItem& value)
//   : m_parent(parent), m_value(value)
//{
//}

ServerInfoItem* ServerInfoItem::appendChild(ServerInfoItemPtr item)
{
   if (!item) { return nullptr; }
   const auto index{ m_childs.size() };
   m_childs.push_back(std::move(item));
   return m_childs.at(index).get();
}

ServerInfoItem* ServerInfoItem::getChild(int row) const
{
   return m_childs.at(row).get();
}

int ServerInfoItem::childCount() const
{
   return m_childs.size();
}

//int TreeItem::columnCount() const
//{
//   return m_value.size();
//}

const SingleValueItem& ServerInfoItem::data(int column) const
{
   return m_value;
}

int ServerInfoItem::row() const
{
   if (m_parent)
   {
      return m_parent->indexOf(this);
   }
   return 0;
}

ServerInfoItem* ServerInfoItem::getParent() const
{
   return m_parent;
}

int ServerInfoItem::indexOf(const ServerInfoItem* item) const
{
   auto isTreeItem = [item](const auto& child) -> bool { return item == child.get(); };
   const auto found = std::find_if(m_childs.cbegin(), m_childs.cend(), isTreeItem);
   if (found != m_childs.cend())
   {
      return std::distance(m_childs.cbegin(), found);
   }
   return -1;
}

void ServerInfoItem::logItemRecursive(int padding) const
{
   logger::info("");
   //LOGGER_INFO(QString("%1 [childs %2; row %3]")
   //   .arg(m_value.m_label).arg(m_childs.size())
   //   .arg(row()).prepend(QString(padding, ' '))
   //);
   for (const auto& child : m_childs)
   {
      child->logItemRecursive(padding + 2);
   }
}

//////////////////////////////////////////////////////////////////////////////////////////

ConfigEditorModel::ConfigEditorModel()
{
}

void ConfigEditorModel::updateModel()
{
   beginResetModel();
   //setupModelData(info);
   endResetModel();
}

int ConfigEditorModel::columnCount(const QModelIndex& parent) const
{
   if (!m_rootItem)
   {
      return 0;
   }
   return 1;
}

int ConfigEditorModel::rowCount(const QModelIndex& parent) const
{
   if (!m_rootItem)
   {
      return 0;
   }

   //if (parent.column() > 0)
   //{
   //   return 0;
   //}

   if (!parent.isValid())
   {
      return m_rootItem->childCount();
   }

   const auto* parentItem{ static_cast<ServerInfoItem*>(parent.internalPointer()) };
   //P_CHKPTR(parentItem, "Internal Pointer Nullptr");
   return parentItem->childCount();
}

QModelIndex ConfigEditorModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!m_rootItem)
   {
      return QModelIndex{};
   }

   if (!hasIndex(row, column, parent))
   {
      return QModelIndex();
   }

   ServerInfoItem* item{ m_rootItem.get() };
   if (parent.isValid())
   {
      item = static_cast<ServerInfoItem*>(parent.internalPointer());
   }

   //P_CHKPTR(item, "TreeItem invalid");
   if (ServerInfoItem* childItem = item->getChild(row))
   {
      return createIndex(row, column, childItem);
   }

   return QModelIndex();
}

QModelIndex ConfigEditorModel::parent(const QModelIndex& index) const
{
   if (!index.isValid())
   {
      return QModelIndex();
   }

   const auto* childItem{ static_cast<ServerInfoItem*>(index.internalPointer()) };
   ServerInfoItem* parentItem = childItem->getParent();

   //P_CHKPTR(parentItem, "parent item invalid");
   if (parentItem == m_rootItem.get())
   {
      return QModelIndex();
   }

   return createIndex(parentItem->row(), 0, parentItem);
}

QVariant ConfigEditorModel::data(const QModelIndex& index, int role) const
{
   if (!index.isValid())
   {
      return QVariant();
   }

   //#todoTG Qt::DecorationRole ??? Icon
   if (role != Qt::DisplayRole && role != Qt::ForegroundRole && role != Qt::FontRole)
   {
      return QVariant();
   }

   const auto* item{ static_cast<ServerInfoItem*>(index.internalPointer()) };
   //P_CHKPTR(item, "index item invalid");
   const SingleValueItem& value{ item->data(index.column()) };

   switch (role)
   {
   case Qt::DisplayRole:
      return value.m_label;
   case Qt::ForegroundRole:
      return QBrush(value.m_color);
   case Qt::FontRole:
      QFont boldFont;
      boldFont.setBold(value.m_isBold);
      return boldFont;
   }

   return {};
}

Qt::ItemFlags ConfigEditorModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
   {
      return Qt::NoItemFlags;
   }

   return QAbstractItemModel::flags(index);
}

//////////////////////////////////////////////////////////////////////////////////////////

//void ConfigEditorModel::printPointer(void* pointer) const
//{
//   LOGGER_DEBUG(QString("0x%1").arg(
//      (quintptr)pointer, 
//      QT_POINTER_SIZE * 2, 16, QChar('0')));
//}
//
//void ConfigEditorModel::setupModelData(const ServerInfo& info)
//{
//   m_rootItem = createTreeItem(nullptr, SingleValueItem{"root"});
//   m_rootItem->appendChild(createServerItem(info, m_rootItem.get()));
//   m_rootItem->appendChild(createConnectItem(info, m_rootItem.get()));
//   m_rootItem->appendChild(createLicenceItem(info, m_rootItem.get()));
//   m_rootItem->appendChild(createReservationItem(info, m_rootItem.get()));
//
//   // print root item recurse 
//   //m_rootItem->logItemRecursive();
//}
//
//ServerInfoItemPtr ConfigEditorModel::createTreeItem(ServerInfoItem* parent, SingleValueItem value)
//{
//   return std::make_unique<ServerInfoItem>(parent, value);
//}
//
//ServerInfoItemPtr ServerInfoModel::createServerItem(const ServerInfo& info, ServerInfoItem* parent)
//{
//   ServerInfoItemPtr serverHeader{ nullptr };
//   switch (info.m_serverState)
//   {
//   case PlantServerBaseConfig::DEVELOP_SERVER_STATE:
//   {
//      serverHeader = createTreeItem(parent, SingleValueItem{
//         "Server ist im Entwicklungsbetrieb", ColorProvider::RED}
//      );
//
//      serverHeader->appendChild(createTreeItem(serverHeader.get(), SingleValueItem{
//         "nicht bei Kunden verwenden!", ColorProvider::RED
//         }
//      ));
//   }
//   break;
//   case PlantServerBaseConfig::LAUNCH_SERVER_STATE:
//   {
//      serverHeader = createTreeItem(parent, SingleValueItem{ 
//         "Server ist im Startbetrieb", ColorProvider::ORANGE }
//      );
//      serverHeader->appendChild(createTreeItem(serverHeader.get(), SingleValueItem{
//         "nicht dauerhaft verwenden!", ColorProvider::ORANGE }
//      ));
//   }
//   break;
//   case PlantServerBaseConfig::RUN_SERVER_STATE:
//   default: 
//   {
//      serverHeader = createTreeItem(parent, SingleValueItem{ 
//         "Server ist im Kundenbetrieb", ColorProvider::GREEN }
//      );
//      break;
//   }
//   }
//
//   serverHeader->appendChild(createTreeItem(serverHeader.get(), SingleValueItem{
//      QString("Läuft seit %1")
//      .arg(ValueFormatter::dateTimeToLongString(info.m_startupTime, true)),
//      }
//   ));
//
//   return serverHeader;
//}
//
//ServerInfoItemPtr ServerInfoModel::createConnectItem(const ServerInfo& info, ServerInfoItem* parent)
//{
//   auto connectHeader = createTreeItem(parent, SingleValueItem{ "Verbindungen" });
//
//   connectHeader->appendChild(createTreeItem(connectHeader.get(), 
//      SingleValueItem{QString("%1 Benutzer angemeldet").arg(info.m_userCount)}
//   ));
//
//   if (info.m_isConnectionActive)
//   {
//      auto color = ColorProvider::GRAY;
//      if (info.m_serverState == PlantServerBaseConfig::DEVELOP_SERVER_STATE && 
//         info.m_thriftPortNumber != ConnectionServerConfig::STANDARD_THRIFT_PORT)
//      {
//         color = ColorProvider::RED;
//      }
//
//      connectHeader->appendChild(createTreeItem(connectHeader.get(), 
//         SingleValueItem{QString("Thrift Port %1: %2 broadcasts, %3 calls in %4h")
//         .arg(info.m_thriftPortNumber)
//         .arg(info.m_broadCastCount)
//         .arg(info.m_callCount)
//         .arg((info.m_broadCastPeriod / (60 * 60)) + 1), color}
//      ));
//   }
//   else
//   {
//      connectHeader->appendChild(createTreeItem(connectHeader.get(), 
//         SingleValueItem{QString("Thrift Port %1: nicht bereit").arg(info.m_thriftPortNumber), ColorProvider::RED}
//      ));
//   }
//
//   const DatabaseConnectionConfig& connectionConfig =  DatabaseConnectionPool::getInstance().getDatabaseConnectionConfig();
//   connectHeader->appendChild(createTreeItem(connectHeader.get(), 
//      SingleValueItem{QString("Datenbank: %1@%2")
//      .arg(connectionConfig.getDatabaseName())
//      .arg(connectionConfig.getHost())}
//   ));
//
//   return connectHeader;
//}
//
//ServerInfoItemPtr ServerInfoModel::createLicenceItem(const ServerInfo& info, ServerInfoItem* parent)
//{
//   static const QIcon EMS_CLIENT_GUI_ICON(":/Resources/emsclientgui.png");
//   static const QIcon SYSTEM_VIEWER_ICON(":/Resources/systemviewer.png");
//   static const QIcon EMS_CUSTOM_PALLET_GUI_ICON(":/Resources/emscustompalletgui.png");
//   static const QIcon STOP_ICON(":/Resources/stop.png");
//
//   auto licenseHeader = createTreeItem(parent, SingleValueItem{ "Lizenzen" });
//
//   for (const LicenceInfo& licenceInfo : info.m_licenceInfoList)
//   {
//      auto label = tr("Nr. %1 (%2) - %3")
//         .arg(licenceInfo.m_licenceKey)
//         .arg(tr(licenceInfo.m_usage.toUtf8().data()))
//         .arg(tr(licenceInfo.m_licenceDescription.toUtf8().data())
//         );
//
//      QIcon licenceInfoIcon;
//      switch (licenceInfo.m_allowedClientType)
//      {
//      case ClientType::CLIENT:
//         licenceInfoIcon = EMS_CLIENT_GUI_ICON;
//         break;
//      case ClientType::SYSTEMVIEWER:
//         licenceInfoIcon = SYSTEM_VIEWER_ICON;
//         break;
//      case ClientType::CUSTOM_GUI:
//         licenceInfoIcon = EMS_CUSTOM_PALLET_GUI_ICON;
//         break;
//      default:
//         licenceInfoIcon = STOP_ICON;
//      }
//
//      auto licenceItem = licenseHeader->appendChild(createTreeItem(
//         licenseHeader.get(), SingleValueItem{label}
//      ));
//
//      for (const QString& userDescription : licenceInfo.m_userHostList)
//      {
//         licenceItem->appendChild(createTreeItem(
//            licenceItem, SingleValueItem{userDescription}
//         ));
//      }
//   }
//
//   return licenseHeader;
//}
//
//ServerInfoItemPtr ServerInfoModel::createReservationItem(const ServerInfo& info, ServerInfoItem* parent)
//{
//   if (!info.m_reservationList.empty())
//   {
//      auto reservationHeader = createTreeItem(parent, 
//         SingleValueItem{"Anstehende Reservierungen"});
//
//      for (const QString& value : info.m_reservationList)
//      {
//         reservationHeader->appendChild(
//            createTreeItem(reservationHeader.get(), SingleValueItem{value}));
//      }
//
//      return reservationHeader;
//   }
//   return nullptr;
//}
//
//void ServerInfoDockWidget::updateNewViewModel(const ServerInfo & info)
//{
//   m_treeModel->updateModelInfo(info);
//}
//
//void ServerInfoDockWidget::updateOldViewModel(const ServerInfo & info)
//{
//   m_model = std::make_unique<QStandardItemModel>(0, COLUMN_COUNT);
//   m_model->setSortRole(ROLE_SORT_KEY);
//
//   QStandardItem* serverStateHeaderItem = new QStandardItem();
//   QFont font = serverStateHeaderItem->font();
//   font.setBold(true);      
//   serverStateHeaderItem->setFont(font);
//   switch (info.m_serverState)
//   {
//   case PlantServerBaseConfig::DEVELOP_SERVER_STATE:
//   {
//      serverStateHeaderItem->setForeground(ColorProvider::getColor(ColorProvider::RED));
//      serverStateHeaderItem->setText(tr("Server ist im Entwicklungsbetrieb"));
//      appendChildren(serverStateHeaderItem, tr("nicht bei Kunden verwenden!"), ColorProvider::getColor(ColorProvider::RED));         
//   }
//   break;
//   case PlantServerBaseConfig::LAUNCH_SERVER_STATE:
//   {
//      serverStateHeaderItem->setForeground(QBrush(ColorProvider::getColor(ColorProvider::ORANGE)));
//      serverStateHeaderItem->setText(tr("Server ist im Startbetrieb"));
//      appendChildren(serverStateHeaderItem, tr("nicht dauerhaft verwenden!"), ColorProvider::getColor(ColorProvider::ORANGE));
//   }
//   break;
//   case PlantServerBaseConfig::RUN_SERVER_STATE:
//   default: 
//   {
//      serverStateHeaderItem->setForeground(QBrush(ColorProvider::getColor(ColorProvider::GREEN)));
//      serverStateHeaderItem->setText(tr("Server ist im Kundenbetrieb"));
//      break;
//   }
//   }
//
//   QString startupDateTimeString = tr("Läuft seit %1").arg(ValueFormatter::dateTimeToLongString(info.m_startupTime, true));
//   appendChildren(serverStateHeaderItem, startupDateTimeString);
//   m_model->appendRow(serverStateHeaderItem);
//
//   QStandardItem* connectionHeaderItem = new QStandardItem();
//   connectionHeaderItem->setText(tr("Verbindungen"));
//   m_model->appendRow(connectionHeaderItem);
//
//   appendChildren(connectionHeaderItem, tr("%1 Benutzer angemeldet").arg(info.m_userCount));
//
//   if (info.m_isConnectionActive)
//   {
//      QColor color = Qt::black;
//      if (info.m_serverState == PlantServerBaseConfig::DEVELOP_SERVER_STATE && 
//         info.m_thriftPortNumber != ConnectionServerConfig::STANDARD_THRIFT_PORT)
//      {
//         color = Qt::red;
//      }
//
//      appendChildren(connectionHeaderItem, tr("Thrift Port %1: %2 broadcasts, %3 calls in %4h")
//         .arg(info.m_thriftPortNumber)
//         .arg(info.m_broadCastCount)
//         .arg(info.m_callCount)
//         .arg((info.m_broadCastPeriod / (60 * 60)) + 1), color);
//   }
//   else
//   {
//      appendChildren(connectionHeaderItem, tr("Thrift Port %1: nicht bereit").arg(info.m_thriftPortNumber), Qt::red);
//   }
//
//   const DatabaseConnectionConfig& connectionConfig =  DatabaseConnectionPool::getInstance().getDatabaseConnectionConfig();   
//   appendChildren(connectionHeaderItem, tr("Datenbank: %1@%2")
//      .arg(connectionConfig.getDatabaseName())
//      .arg(connectionConfig.getHost()));
//
//   QStandardItem* licenceSuperHeaderItem = new QStandardItem();
//   licenceSuperHeaderItem->setText(tr("Lizenzen"));
//   m_model->appendRow(licenceSuperHeaderItem);
//   foreach(LicenceInfo licenceInfo , info.m_licenceInfoList)
//   {
//      QStandardItem* licenceHeaderItem = new QStandardItem();
//      licenceHeaderItem->setText(tr("Nr. %1 (%2) - %3")
//         .arg(licenceInfo.m_licenceKey).arg(tr(licenceInfo.m_usage.toUtf8().data())).arg(tr(licenceInfo.m_licenceDescription.toUtf8().data())));
//
//      static const QIcon EMS_CLIENT_GUI_ICON(":/Resources/emsclientgui.png");
//      static const QIcon SYSTEM_VIEWER_ICON(":/Resources/systemviewer.png");
//      static const QIcon EMS_CUSTOM_PALLET_GUI_ICON(":/Resources/emscustompalletgui.png");
//      static const QIcon STOP_ICON(":/Resources/stop.png");
//
//      switch(licenceInfo.m_allowedClientType)
//      {
//      case ClientType::CLIENT:
//         licenceHeaderItem->setIcon(EMS_CLIENT_GUI_ICON);
//         break;
//      case ClientType::SYSTEMVIEWER:
//         licenceHeaderItem->setIcon(SYSTEM_VIEWER_ICON);
//         break;
//      case ClientType::CUSTOM_GUI:
//         licenceHeaderItem->setIcon(EMS_CUSTOM_PALLET_GUI_ICON);
//         break;
//      default:
//         licenceHeaderItem->setIcon(STOP_ICON);
//      }
//
//      foreach(QString userDescription, licenceInfo.m_userHostList)
//      {
//         appendChildren(licenceHeaderItem, userDescription);
//      }
//      licenceSuperHeaderItem->appendRow(licenceHeaderItem);
//   }
//
//   if (!info.m_reservationList.isEmpty())
//   {
//      QStandardItem* reservationHeaderItem = new QStandardItem();
//      reservationHeaderItem->setText(tr("Anstehende Reservierungen"));      
//      foreach(QString value, info.m_reservationList)
//      {
//         appendChildren(reservationHeaderItem, value);
//      }
//      m_model->appendRow(reservationHeaderItem);
//   }
//
//   m_ui.infoTreeView->setModel(m_model.get());
//}
//
//void ServerInfoDockWidget::appendChildren(QStandardItem* headerItem, QString value, QColor color)
//{
//   QStandardItem* rowItem = new QStandardItem();
//   rowItem->setText(tr(value.toUtf8().data()));   
//   rowItem->setForeground(QBrush(color));
//   headerItem->appendRow(rowItem);
//}

///////////////////////////////////////////////////////////////////

ConfigEditorProxy::ConfigEditorProxy()
{
}

bool ConfigEditorProxy::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
   return false;
}

bool ConfigEditorProxy::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
   return false;
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)