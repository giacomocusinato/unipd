#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "storeitem.h"

class ItemEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ItemEditor(QStringList, QWidget *parent = 0);
private:
    QLineEdit *titleEdit;
    QLineEdit *devEdit;
    QDoubleSpinBox *ratingEdit;
    QDoubleSpinBox *priceEdit;
    QStringList item_data;
    QString icon_uri(QString);
signals:
    void itemModified(QStringList, QString);
    
public slots:
    void manageNewData();
    void removeItem();
};

#endif // ITEMEDITOR_H
