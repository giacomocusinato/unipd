#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H

#include <QAbstractTableModel>

#include "container.h"
#include "smartpointer.h"

class ContainerModel : public QAbstractTableModel
{
public:
    ContainerModel(QObject* =0);

    int columnCount(const QModelIndex&) const;
    int rowCount(const QModelIndex&) const;
    QVariant data(const QModelIndex&, int) const;

    void setViewContainer(container<SmartPointer> *);
    container<SmartPointer> getViewContainer();

    inline void res() { reset(); }
private:
    container<SmartPointer> *viewContainer;
    static int columns;
};

#endif // CONTAINERMODEL_H
