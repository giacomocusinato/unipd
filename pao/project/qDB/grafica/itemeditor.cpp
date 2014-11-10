#include <QGridLayout>
#include <QFile>

#include "itemeditor.h"
#include "tableitem.h"

ItemEditor::ItemEditor(QStringList list, QWidget *parent) :
    QWidget(parent), item_data(list)
{
    QLabel *image = new QLabel();
    image->setPixmap(QPixmap(icon_uri(list[0])));

    QLabel *title = new QLabel("Title: ");
    titleEdit = new QLineEdit(list[0]);

    QLabel *dev = new QLabel("Developer: ");;
    devEdit = new QLineEdit(list[1]);

    QLabel *rating = new QLabel("Rating: ");
    ratingEdit = new QDoubleSpinBox();
    ratingEdit->setValue(list[2].toDouble());
    ratingEdit->setMaximum(5);
    ratingEdit->setMinimum(0);

    QLabel *price = new QLabel("Price: ");
    priceEdit = new QDoubleSpinBox();
    priceEdit->setValue(list[3].toDouble());
    priceEdit->setMinimum(0);

    QPushButton *confirm = new QPushButton("Apply");
    QPushButton *remove = new QPushButton("Delete Item");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(image, 0, 0, 1, 2);
    layout->addWidget(title, 1, 0);
    layout->addWidget(titleEdit, 1, 1);
    layout->addWidget(dev, 2, 0);
    layout->addWidget(devEdit, 2, 1);
    layout->addWidget(rating, 3, 0);
    layout->addWidget(ratingEdit, 3, 1);
    layout->addWidget(price, 4, 0);
    layout->addWidget(priceEdit, 4, 1);
    layout->addWidget(confirm, 5, 0);
    layout->addWidget(remove, 5, 1);

    this->setLayout(layout);

    connect(confirm, SIGNAL(clicked()), this, SLOT(manageNewData()));
    connect(remove, SIGNAL(clicked()), this, SLOT(removeItem()));

}

void ItemEditor::manageNewData()
{
    if (titleEdit->text().isEmpty() || devEdit->text().isEmpty())
    {
        if (titleEdit->text().isEmpty())
            titleEdit->setStyleSheet("border: 1px solid red");
        if (devEdit->text().isEmpty())
            devEdit->setStyleSheet("border: 1px solid red");
    }
    else
    {
        QStringList list;
        list.push_back(titleEdit->text());
        list.push_back(devEdit->text());
        list.push_back(QString::number(ratingEdit->value()));
        list.push_back(QString::number(priceEdit->value()));

        emit itemModified(list, item_data[0]);

        this->close();
    }
}

void ItemEditor::removeItem()
{
    emit itemModified(QStringList(), item_data[0]);

    this->close();
}

QString ItemEditor::icon_uri(QString s)
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
