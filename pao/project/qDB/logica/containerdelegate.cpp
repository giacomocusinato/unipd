#include <QPainter>
#include <QLineEdit>
#include <QDebug>

#include "containerdelegate.h"
#include "tableitem.h"

ContainerDelegate::ContainerDelegate(QObject *parent): QStyledItemDelegate(parent) {}

void ContainerDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    QStringList data = index.data().toStringList();
    if (data.empty())
    {
        QPixmap pixmap = QPixmap::grabWidget(new QWidget());
        painter->drawPixmap(option.rect, pixmap);
        return;
    }

    TableItem item(data);
    QPixmap pixmap = QPixmap::grabWidget(&item);
    painter->drawPixmap(option.rect, pixmap);
}


