#include <QHeaderView>
#include <QPalette>
#include <QDebug>

#include "containerview.h"

ContainerView::ContainerView(QWidget *parent): QTableView(parent)
{
    verticalHeader()->setDefaultSectionSize(210);
    horizontalHeader()->setDefaultSectionSize(120);

    QPalette p;
    p.setColor(QPalette::Base, QColor(240,240,240));
    setPalette(p);

    setBackgroundRole(QPalette::Base);
    setCornerButtonEnabled(false);
    setShowGrid(false);
    setStyleSheet("border: none");
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setFixedSize(613, 650);
    QHeaderView *hh = horizontalHeader();
    hh->hide();

    QHeaderView *vh = verticalHeader();
    vh->hide();
}

void ContainerView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList list = selected.indexes();
    if (list.size() > 0)
    {
        emit editIndex(list.first());
    }
}
