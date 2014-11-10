#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QWidget>
#include <QLabel>
#include <QStringList>

#include "storeitem.h"
#include "ratinglabel.h"

class TableItem : public QWidget
{
    Q_OBJECT
public:
    TableItem(const StoreItem*, QWidget* =0);
    TableItem(const QStringList&, QWidget* =0);
private:
    QString icon_uri(QString);
};

#endif // TABLEITEM_H
