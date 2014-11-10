#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QGroupBox>

#include "addappview.h"

AddAppView::AddAppView(QWidget *parent) :
    QWidget(parent)
{
    QLabel *title = new QLabel("Title: ");
    titleEdit = new QLineEdit();

    QLabel *dev = new QLabel("Developer: ");;
    devEdit = new QLineEdit();

    QLabel *rating = new QLabel("Rating: ");
    ratingEdit = new QDoubleSpinBox();
    ratingEdit->setMaximum(5);
    ratingEdit->setMinimum(0);

    QLabel *nrating = new QLabel("Ratings number: ");
    nratingEdit = new QSpinBox();
    nratingEdit->setMinimum(0);

    QLabel *price = new QLabel("Price: ");
    priceEdit = new QDoubleSpinBox();
    priceEdit->setMinimum(0);

    QLabel *localization = new QLabel("Localization: ");
    localizationEdit = new QLineEdit("Global");

    newsCheck = new QCheckBox("News");
    newsCheck->setChecked(true);
    utilityCheck = new QCheckBox("Utility");
    socialCheck = new QCheckBox("Social");
    multimediaCheck = new QCheckBox("Multimedia");

    QButtonGroup *buttonGroup = new QButtonGroup();
    buttonGroup->addButton(newsCheck);
    buttonGroup->addButton(utilityCheck);
    buttonGroup->addButton(socialCheck);
    buttonGroup->addButton(multimediaCheck);

    QGridLayout *groupBoxLayout = new QGridLayout();
    groupBoxLayout->addWidget(newsCheck, 0, 0);
    groupBoxLayout->addWidget(utilityCheck, 0, 1);
    groupBoxLayout->addWidget(socialCheck, 1, 0);
    groupBoxLayout->addWidget(multimediaCheck, 1, 1);
    QGroupBox *groupBox = new QGroupBox("Category");
    groupBox->setStyleSheet("QGroupBox {border:1px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    groupBox->setLayout(groupBoxLayout);
    groupBox->setMinimumHeight(120);

    QPushButton *confirm = new QPushButton("Add");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(title, 1, 0);
    layout->addWidget(titleEdit, 1, 1);
    layout->addWidget(dev, 2, 0);
    layout->addWidget(devEdit, 2, 1);
    layout->addWidget(nrating, 3, 0);
    layout->addWidget(nratingEdit, 3, 1);
    layout->addWidget(rating, 4, 0);
    layout->addWidget(ratingEdit, 4, 1);
    layout->addWidget(price, 5, 0);
    layout->addWidget(priceEdit, 5, 1);
    layout->addWidget(localization, 6, 0);
    layout->addWidget(localizationEdit, 6, 1);
    layout->addWidget(groupBox, 7, 0, 3, 0);
    layout->addWidget(confirm, 10, 0);

    this->setLayout(layout);

    connect(confirm, SIGNAL(clicked()), this, SLOT(manageNewData()));
}

void AddAppView::manageNewData()
{
    if (titleEdit->text().isEmpty() || devEdit->text().isEmpty())
    {
        if (titleEdit->text().isEmpty())
            titleEdit->setStyleSheet("border: 1px solid red");
        if (devEdit->text().isEmpty())
            devEdit->setStyleSheet("border: 1px solid red");
        return;
    }
    titleEdit->setStyleSheet("border: 1px solid gray");
    devEdit->setStyleSheet("border: 1px solid gray");

    if (localizationEdit->text().isEmpty())
    {
        localizationEdit->setText("Global");
    }

    if (nratingEdit->value() == 0 && ratingEdit->value() != 0)
    {
        nratingEdit->setStyleSheet("border: 1px solid red");
        return;
    }

    App::category cat;
    if (newsCheck->checkState())
        cat = App::News;
    else if (socialCheck->checkState())
        cat = App::Social;
    else if (utilityCheck->checkState())
        cat = App::Utility;
    else
        cat = App::Multimedia;

    App app(titleEdit->text().toStdString(), titleEdit->text().toStdString(), ratingEdit->value(), nratingEdit->value(), cat, localizationEdit->text().toStdString(), priceEdit->value());
    emit newAppAdded(app);
    emit updateLocalizationList(localizationEdit->text());

    this->close();
}
