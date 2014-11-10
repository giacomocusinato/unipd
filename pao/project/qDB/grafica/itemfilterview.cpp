#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

#include "itemfilterview.h"

ItemFilterView::ItemFilterView(QStringListModel *model, QWidget *parent) :
    QWidget(parent), localizationModel(model)
{

    localizationView = new QListView();
    localizationView->setEditTriggers(QListView::NoEditTriggers);
    localizationView->setModel(localizationModel);
    localizationView->setCurrentIndex(localizationModel->index(0,0));

    freeAppCheckBox = new QCheckBox("Free App");
    paidAppCheckBox = new QCheckBox("Paid App");
    socialCheckBox = new QCheckBox("Social");
    newsCheckBox = new QCheckBox("News");
    multimediaCheckBox = new QCheckBox("Multimedia");
    utilityCheckBox = new QCheckBox("Utility");

    QGridLayout *appLayout = new QGridLayout();
    appLayout->addWidget(freeAppCheckBox, 0, 0);
    appLayout->addWidget(paidAppCheckBox, 0, 1);
    appLayout->addWidget(socialCheckBox, 1, 0);
    appLayout->addWidget(newsCheckBox, 1, 1);
    appLayout->addWidget(multimediaCheckBox, 2, 0);
    appLayout->addWidget(utilityCheckBox, 2, 1);
    appLayout->addWidget(localizationView, 3, 0, 1, 2);

    QGroupBox *appGroupBox = new QGroupBox("Filter apps");
    appGroupBox->setStyleSheet(groupBoxStyle);
    appGroupBox->setLayout(appLayout);


    freeGameCheckBox = new QCheckBox("Free Game");
    paidGameCheckBox = new QCheckBox("Paid Game");
    puzzleCheckBox = new QCheckBox("Puzzle");
    actionCheckBox = new QCheckBox("Action");
    platformerCheckBox = new QCheckBox("Platformer");
    strategyCheckBox = new QCheckBox("Strategy");
    xboxCheckBox = new QCheckBox("Xbox");
    indieCheckBox = new QCheckBox("Indie");

    QGridLayout *gameLayout = new QGridLayout();
    gameLayout->addWidget(freeGameCheckBox, 0, 0);
    gameLayout->addWidget(paidGameCheckBox, 0, 1);
    gameLayout->addWidget(puzzleCheckBox, 1, 0);
    gameLayout->addWidget(actionCheckBox, 1, 1);
    gameLayout->addWidget(platformerCheckBox, 2, 0);
    gameLayout->addWidget(strategyCheckBox, 2, 1);
    gameLayout->addWidget(xboxCheckBox, 3, 0);
    gameLayout->addWidget(indieCheckBox, 3, 1);

    QGroupBox *gameGroupBox = new QGroupBox("Filter games");
    gameGroupBox->setStyleSheet(groupBoxStyle);
    gameGroupBox->setLayout(gameLayout);


    QPushButton *button = new QPushButton("Apply filter");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(appGroupBox);
    mainLayout->addWidget(gameGroupBox);
    mainLayout->addWidget(button);

    this->setLayout(mainLayout);

    freeAppCheckBox->setChecked(true);
    paidAppCheckBox->setChecked(true);
    freeGameCheckBox->setChecked(true);
    paidGameCheckBox->setChecked(true);
    socialCheckBox->setChecked(true);
    newsCheckBox->setChecked(true);
    multimediaCheckBox->setChecked(true);
    utilityCheckBox->setChecked(true);
    puzzleCheckBox->setChecked(true);
    actionCheckBox->setChecked(true);
    platformerCheckBox->setChecked(true);
    strategyCheckBox->setChecked(true);
    xboxCheckBox->setChecked(true);
    indieCheckBox->setChecked(true);

    connect(button, SIGNAL(clicked()), this, SLOT(filterManager()));


}

QString ItemFilterView::groupBoxStyle = "QGroupBox {border:1px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}";

void ItemFilterView::filterManager() const
{
    QHash<QString, int> hash;

    hash["freeapp"] = freeAppCheckBox->isChecked();
    hash["paidapp"] = paidAppCheckBox->isChecked();
    hash["social"] = socialCheckBox->isChecked();
    hash["news"] = newsCheckBox->isChecked();
    hash["multimedia"] = multimediaCheckBox->isChecked();
    hash["utility"] = utilityCheckBox->isChecked();
    hash["freegame"] = freeGameCheckBox->isChecked();
    hash["paidgame"] = paidGameCheckBox->isChecked();
    hash["puzzle"] = puzzleCheckBox->isChecked();
    hash["action"] = actionCheckBox->isChecked();
    hash["platformer"] = platformerCheckBox->isChecked();
    hash["strategy"] = strategyCheckBox->isChecked();
    hash["xbox"] = xboxCheckBox->isChecked();
    hash["indie"] = indieCheckBox->isChecked();

    QModelIndex index = localizationView->currentIndex();
    QString localization = localizationModel->data(index, Qt::DisplayRole).toString();
    hash[localization] = 2;

    emit filterChanged(hash);
}

void ItemFilterView::updateData() const
{
    filterManager();
}

void ItemFilterView::updateLocalizationModel(QString localization)
{
    QStringList list = localizationModel->stringList();
    if (list.contains(localization))
    {
        return;
    }
    list.push_back(localization);

    localizationModel = new QStringListModel(list);
    localizationView->setModel(localizationModel);
}

void ItemFilterView::setLocalizationModel(QStringListModel *model)
{
    localizationModel = model;
    localizationView ->setModel(localizationModel);
}
