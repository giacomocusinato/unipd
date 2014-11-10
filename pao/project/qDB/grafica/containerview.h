#ifndef CONTAINERVIEW_H
#define CONTAINERVIEW_H

#include <QTableView>

#include "containerdelegate.h"

class ContainerView : public QTableView {
    Q_OBJECT
public:
    ContainerView(QWidget* =0);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
signals:
    void editIndex(QModelIndex);
};

#endif // CONTAINERVIEW_H
