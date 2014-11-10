#ifndef CONTAINERDELEGATE_H
#define CONTAINERDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class ContainerDelegate : public QStyledItemDelegate
{
public:
    ContainerDelegate(QObject *);

    /* Overridden classes */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CONTAINERDELEGATE_H
