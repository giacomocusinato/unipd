#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QGroupBox>

#include "addgameview.h"

AddGameView::AddGameView(QWidget *parent) :
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

    puzzleCheck = new QCheckBox("Puzzle");
    puzzleCheck->setChecked(true);
    actionCheck = new QCheckBox("Action");
    strategyCheck = new QCheckBox("Strategy");
    platformerCheck = new QCheckBox("Platformer");

    QButtonGroup *buttonGroup = new QButtonGroup();
    buttonGroup->addButton(puzzleCheck);
    buttonGroup->addButton(actionCheck);
    buttonGroup->addButton(strategyCheck);
    buttonGroup->addButton(platformerCheck);

    QGridLayout *groupBoxLayout = new QGridLayout();
    groupBoxLayout->addWidget(puzzleCheck, 0, 0);
    groupBoxLayout->addWidget(actionCheck, 0, 1);
    groupBoxLayout->addWidget(strategyCheck, 1, 0);
    groupBoxLayout->addWidget(platformerCheck, 1, 1);
    QGroupBox *groupBox = new QGroupBox("Category");
    groupBox->setStyleSheet("QGroupBox {border:1px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    groupBox->setLayout(groupBoxLayout);
    groupBox->setMinimumHeight(120);

    indieCheck = new QCheckBox("Indie");
    indieCheck->setChecked(true);
    xboxCheck = new QCheckBox("Xbox");

    QButtonGroup *buttonGroup2 = new QButtonGroup();
    buttonGroup2->addButton(indieCheck);
    buttonGroup2->addButton(xboxCheck);

    QGridLayout *groupBox2Layout = new QGridLayout();
    groupBox2Layout->addWidget(indieCheck, 0, 0);
    groupBox2Layout->addWidget(xboxCheck, 0, 1);
    QGroupBox *groupBox2 = new QGroupBox("Brand");
    groupBox2->setStyleSheet("QGroupBox {border:1px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    groupBox2->setLayout(groupBox2Layout);
    groupBox2->setMinimumHeight(84);

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
    layout->addWidget(groupBox, 6, 0, 3, 0);
    layout->addWidget(groupBox2, 9, 0, 2, 0);
    layout->addWidget(confirm, 11, 0);

    this->setLayout(layout);

    connect(confirm, SIGNAL(clicked()), this, SLOT(manageNewData()));
}

void AddGameView::manageNewData()
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

    if (nratingEdit->value() == 0 && ratingEdit->value() != 0)
    {
        nratingEdit->setStyleSheet("border: 1px solid red");
        return;
    }

    Game::category cat;
    if (puzzleCheck->checkState())
        cat = Game::Puzzle;
    else if (actionCheck->checkState())
        cat = Game::Action;
    else if (platformerCheck->checkState())
        cat = Game::Platformer;
    else
        cat = Game::Strategy;

    Game game(titleEdit->text().toStdString(), devEdit->text().toStdString(), ratingEdit->value(), nratingEdit->value(), cat, priceEdit->value(), xboxCheck->checkState());
    emit newGameAdded(game);

    this->close();
}
