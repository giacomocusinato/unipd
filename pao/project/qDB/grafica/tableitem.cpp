#include <QPixmap>
#include <QVBoxLayout>
#include <QPainter>
#include <QPolygonF>
#include <QImage>
#include <iostream>
#include <QFile>
#include <QLocale>

#include "tableitem.h"

TableItem::TableItem(const StoreItem* item, QWidget *parent) :
    QWidget(parent)
{
    QString name = QString::fromStdString(item->getTitle());
    QString dev = QString::fromStdString(item->getDeveloper());
    QString price;
    if (item->getPrice() == 0)
        price = "Free";
    else
        price = QString::number(item->getPrice());

    QLabel *iconLabel = new QLabel;
    QLabel *nameLabel = new QLabel(name);
    QLabel *devLabel = new QLabel("by " + dev);
    QLabel *priceLabel = new QLabel(price);
    RatingLabel *ratingLabel = new RatingLabel(item->getQuality());

    QString uri = icon_uri(name);
    QPixmap pixmap(uri);
    iconLabel->setPixmap(pixmap);

    iconLabel->setFixedSize(95, 95);
    nameLabel->setFixedSize(120, 18);
    devLabel->setFixedSize(120, 18);
    priceLabel->setFixedSize(120, 18);
    ratingLabel->setFixedSize(120, 18);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(iconLabel);
    layout->addWidget(nameLabel);
    layout->addWidget(devLabel);
    layout->addWidget(ratingLabel);
    layout->addWidget(priceLabel);
    layout->setSpacing(5);
    this->setLayout(layout);
    this->setFixedSize(120, 210);
}

TableItem::TableItem(const QStringList& list, QWidget *parent) :
    QWidget(parent)
{
    QString rat = list[2];
    QString price = list[3];
    if (price == "0")
        price = "Free";
    else
        price = price + "$";

    QLabel *iconLabel = new QLabel;
    QLabel *nameLabel = new QLabel(list[0]);
    QLabel *devLabel = new QLabel("by " + list[1]);
    RatingLabel *ratingLabel = new RatingLabel(rat.toDouble());
    QLabel *priceLabel = new QLabel(price);

    QString uri = icon_uri(list[0]);
    QPixmap pixmap(uri);
    iconLabel->setPixmap(pixmap);

    iconLabel->setFixedSize(95, 95);
    nameLabel->setFixedSize(120, 18);
    devLabel->setFixedSize(120, 18);
    priceLabel->setFixedSize(120, 18);
    ratingLabel->setFixedSize(120, 18);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(iconLabel);
    layout->addWidget(nameLabel);
    layout->addWidget(devLabel);
    layout->addWidget(ratingLabel);
    layout->addWidget(priceLabel);
    layout->setSpacing(5);
    this->setLayout(layout);
    this->setFixedSize(120, 210);

}

QString TableItem::icon_uri(QString s)
{
    // Remove white spaces and capital letters in the string
    // in order to match the icon uri
    int n = s.size() - 1;
    for (; n>=0; --n)
    {
        if (s.at(n).isSpace())
            s.remove(n, 1);
    }
    s = s.toLower();

    QString uri = ":/Icons/Resources/Icons/" + s + ".png";
    QFile file(uri);
    if (!file.exists())
    {
        uri = ":/Icons/Resources/Icons/default.png";
    }

    return uri;
}

