#include <QStringList>
#include <QDebug>

#include "smartpointer.h"
#include "containermodel.h"

ContainerModel::ContainerModel(QObject *parent) :QAbstractTableModel(parent) {}

int ContainerModel::columns = 5;

int ContainerModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}
int ContainerModel::rowCount(const QModelIndex & /*parent*/) const
{
    return (viewContainer->size() / 5) + 1;
}
QVariant ContainerModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int position = (5*index.row()) + index.column();
        if (position >= viewContainer->size())
        {
            return QStringList();
        }

        QStringList item_info;
        item_info.push_back(QString::fromStdString((*viewContainer)[position]->getTitle()));
        item_info.push_back(QString::fromStdString((*viewContainer)[position]->getDeveloper()));
        item_info.push_back(QString::number((*viewContainer)[position]->getQuality()));
        item_info.push_back(QString::number((*viewContainer)[position]->getPrice()));
        return item_info;
    }
    return QVariant();
}

void ContainerModel::setViewContainer(container<SmartPointer> *cont)
{
    viewContainer = new container<SmartPointer>(*cont);
}

container<SmartPointer> ContainerModel::getViewContainer()
{
    return *viewContainer;
}
