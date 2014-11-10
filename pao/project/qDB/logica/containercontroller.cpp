#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>

#include "containercontroller.h"
#include "game.h"
#include "app.h"
#include "smartpointer.h"

ContainerController::ContainerController(ContainerModel *m, ContainerView *v)
    : model(m), view(v)
{
    ContainerDelegate *delegate = new ContainerDelegate(view);

    // Initialize container
    mainContainer = new container<SmartPointer>();

    /*
    StoreItem* app1 = new App("Instagram", "Burbn Inc.", 4.5, 3560, App::Social);
    StoreItem* app2 = new App("Amazing Weather", "CodeUp", 4.0, 1200, App::Utility, "Global", 1.99);
    StoreItem* app3 = new App("Astronomy Hub", "Bytestorm", 4.8, 1700, App::News);
    StoreItem* app4 = new App("Facebook", "Facebook Inc.", 3.3, 5250, App::Social);
    StoreItem* app5 = new App("LinkedIn", "LinkedIn", 3.8, 900, App::Social);
    StoreItem* app6 = new App("musiXmatch", "Musixmatch", 4.9, 2030, App::Multimedia);
    StoreItem* app7 = new App("myBattery", "Ben Smith", 4.3, 1343, App::Utility, "Global", 0.99);
    StoreItem* app8 = new App("Nextgen Reader", "MetroDev", 4.1, 1400, App::News, "Global", 1.99);
    StoreItem* app9 = new App("Paypal", "Paypal", 2.5, 1800, App::Utility);
    StoreItem* app10 = new App("Photo Editor", "Ryan Stud", 4.5, 1300, App::Multimedia, "Global", 0.99);
    StoreItem* app11 = new App("ProShot", "Imaging House", 5.0, 3000, App::Multimedia, "Global", 2.99);
    StoreItem* app12 = new App("Rai News", "Rai", 3.5, 960, App::News, "Italy");
    StoreItem* app13 = new App("Serie A", "Venetasoft", 4.3, 1340, App::News, "Italy", 1.99);
    StoreItem* app14 = new App("Shazam", "Shazam Ltd", 3.7, 2245, App::Multimedia);
    StoreItem* app15 = new App("Skype", "Microsoft", 4.1, 2100, App::Social);
    StoreItem* app16 = new App("SoundCloud", "SoundCloud", 3.6, 1300, App::Multimedia);
    StoreItem* app17 = new App("Sport News", "MetroDev", 4.1, 750, App::News);
    StoreItem* app18 = new App("Spotify", "Spotify", 2.7, 3000, App::Multimedia);
    StoreItem* app19 = new App("StopWatch", "CodeFromHome", 4.7, 4300, App::Utility);
    StoreItem* app20 = new App("Bing Translator", "Microsoft", 4.0, 2400, App::Utility);
    StoreItem* app21 = new App("Trenitalia", "Trenitalia", 3.6, 1344, App::Utility, "Italy");
    StoreItem* app22 = new App("Whatsapp", "Whatsapp Inc.", 3.2, 6040, App::Social);
    StoreItem* app23 = new App("Wikipedia", "Wikipedia", 4.8, 3500, App::Utility);
    StoreItem* game1 = new Game("War 2", "MetroDev", 3, 300, Game::Action, 0);
    StoreItem* game2 = new Game("Angry Birds Rio", "Rovio", 4.5, 10, Game::Puzzle, 1.99, true);

    mainContainer->push_back(app1);
    mainContainer->push_back(app2);
    mainContainer->push_back(app3);
    mainContainer->push_back(app4);
    mainContainer->push_back(app5);
    mainContainer->push_back(app6);
    mainContainer->push_back(app7);
    mainContainer->push_back(app8);
    mainContainer->push_back(app9);
    mainContainer->push_back(app10);
    mainContainer->push_back(app11);
    mainContainer->push_back(app12);
    mainContainer->push_back(app13);
    mainContainer->push_back(app14);
    mainContainer->push_back(app15);
    mainContainer->push_back(app16);
    mainContainer->push_back(app17);
    mainContainer->push_back(app18);
    mainContainer->push_back(app19);
    mainContainer->push_back(app20);
    mainContainer->push_back(app21);
    mainContainer->push_back(app22);
    mainContainer->push_back(app23);
    mainContainer->push_back(game1);
    mainContainer->push_back(game2);

    */

    model->setViewContainer(mainContainer);
    view->setModel(model);
    view->setItemDelegate(delegate);

    connect(view, SIGNAL(editIndex(QModelIndex)), this, SLOT(editIndex(QModelIndex)));


}

void ContainerController::updateView()
{
    model->setViewContainer(viewCont);
    model->res();
    view->setModel(model);
}

void ContainerController::manageViewItems(QHash<QString,int> hash)
{
    filter = new QHash<QString,int>(hash);

    container<SmartPointer>::const_iterator it = mainContainer->const_begin();
    container<SmartPointer> result;

    for (; it != mainContainer->const_end(); ++it)
    {
        const App* app = dynamic_cast<const App*>(&(**it));

        if (app)
        {
            QString localization = hash.key(2, "Global");
            if (app->getLocalization() == localization.toStdString() || app->getLocalization() == "Global")
            {
                if ((*filter)["freeapp"] && app->getPrice() == 0 && checkItemCategory(app))
                {
                    result.push_front(new App(*(const_cast<App*>(app))));
                }
                else if ((*filter)["paidapp"] && app->getPrice() > 0 && checkItemCategory(app))
                {
                    result.push_front(new App(*(const_cast<App*>(app))));
                }
            }
        }
        else
        {
            const Game* game = dynamic_cast<const Game*>(&(**it));
            if (!game)
                return;

            if ((*filter)["freegame"] && game->getPrice() == 0 && checkItemCategory(game))
            {
                result.push_back(new Game(*(const_cast<Game*>(game))));
            }
            else if ((*filter)["paidgame"] && game->getPrice() > 0 && checkItemCategory(game))
            {
                result.push_back(new Game(*(const_cast<Game*>(game))));
            }
        }
    }

    this->viewCont = new container<SmartPointer>(result);
    this->updateView();
}

bool ContainerController::checkItemCategory(const StoreItem *store_item) const
{
    const App* app = dynamic_cast<const App*>(store_item);

    if (app)
    {
        App::category cat = app->getCategoty();
        if (cat == App::Social && (*filter)["social"])
        {
            return true;
        }
        if (cat == App::News && (*filter)["news"])
        {
            return true;
        }
        if (cat == App::Utility && (*filter)["utility"])
        {
            return true;
        }
        if (cat == App::Multimedia && (*filter)["multimedia"])
        {
            return true;
        }
    }
    else
    {
        const Game* game = dynamic_cast<const Game*>(store_item);
        if (!game)
            return false;

        if (game->isXbox() && (*filter)["xbox"])
        {
            Game::category cat = game->getCategory();
            if (cat == Game::Puzzle && (*filter)["puzzle"])
            {
                return true;
            }
            if (cat == Game::Action && (*filter)["action"])
            {
                return true;
            }
            if (cat == Game::Strategy && (*filter)["strategy"])
            {
                return true;
            }
            if (cat == Game::Platformer && (*filter)["platformer"])
            {
                return true;
            }
        }
        else if (!game->isXbox() && (*filter)["indie"])
        {
            Game::category cat = game->getCategory();
            if (cat == Game::Puzzle && (*filter)["puzzle"])
            {
                return true;
            }
            if (cat == Game::Action && (*filter)["action"])
            {
                return true;
            }
            if (cat == Game::Strategy && (*filter)["strategy"])
            {
                return true;
            }
            if (cat == Game::Platformer && (*filter)["platformer"])
            {
                return true;
            }
        }
    }

    return false;
}

QStringListModel* ContainerController::getLocalizationModel() const
{
    QStringList list;

    container<SmartPointer>::const_iterator it = mainContainer->const_begin();
    for (; it != mainContainer->const_end(); ++it)
    {
        const App* app = dynamic_cast<const App*>(&(**it));

        if (app)
        {
            QString localization = QString::fromStdString(app->getLocalization());
            if(!list.contains(localization))
            {
                list.push_back(localization);
            }
        }
    }

    return new QStringListModel(list);
}

void ContainerController::editIndex(QModelIndex index)
{
    QStringList item_data = model->data(index, Qt::DisplayRole).toStringList();
    if (item_data.empty())
        return;

    ItemEditor *editor = new ItemEditor(item_data);
    editor->show();

    connect(editor, SIGNAL(itemModified(QStringList,QString)), this, SLOT(modifyItem(QStringList,QString)));
}

void ContainerController::modifyItem(QStringList list, QString itemTitle)
{
    if (list.empty())
    {
        container<SmartPointer>::iterator it = mainContainer->begin();
        for(; it != mainContainer->end(); ++it)
        {
            if ((*it)->getTitle() == itemTitle.toStdString())
            {
                mainContainer->remove(*it);
                break;
            }
        }
    }
    else
    {
        container<SmartPointer>::iterator it = mainContainer->begin();
        for(; it != mainContainer->end(); ++it)
        {
            if ((*it)->getTitle() == itemTitle.toStdString())
            {
                (*it)->setTitle(list[0].toStdString());
                (*it)->setDeveloper(list[1].toStdString());
                (*it)->setQuality(list[2].toDouble());
                (*it)->setPrice(list[3].toDouble());
                break;
            }
        }
    }

    emit updateData();
}

void ContainerController::addNewApp(App app)
{
    StoreItem *item = new App(app);
    mainContainer->push_back(item);

    emit updateData();
}

void ContainerController::addNewGame(Game game)
{
    StoreItem *item = new Game(game);
    mainContainer->push_back(item);

    emit updateData();
}

void ContainerController::serializeContainer(QString filename) const
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter *writer = new QXmlStreamWriter();
    writer->setDevice(&file);
    writer->writeStartDocument();
    writer->writeStartElement("items");

    container<SmartPointer>::const_iterator it = mainContainer->const_begin();
    for (; it != mainContainer->const_end(); ++it)
    {
        const App *app = dynamic_cast<const App*>(&(**it));
        if (app)
        {
            QString category;
            App::category cat = app->getCategoty();
            if (cat == App::Social)
            {
                category = "Social";
            }
            else if (cat == App::News)
            {
                 category = "News";
            }
            else if (cat == App::Utility)
            {
                 category = "Utility";
            }
            else //(cat == App::Multimedia)
            {
                 category = "Multimedia";
            }
            writer->writeStartElement("app");
            writer->writeAttribute("title", QString::fromStdString(app->getTitle()));
            writer->writeAttribute("developer", QString::fromStdString(app->getDeveloper()));
            writer->writeAttribute("rating", QString::number(app->getQuality()));
            writer->writeAttribute("nratings", QString::number(app->getRatings()));
            writer->writeAttribute("price", QString::number(app->getPrice()));
            writer->writeAttribute("localization", QString::fromStdString(app->getLocalization()));
            writer->writeAttribute("category", category);
            writer->writeEndElement();
        }
        else
        {
            const Game *game = dynamic_cast<const Game*>(&(**it));

            QString category;
            Game::category cat = game->getCategory();
            if (cat == Game::Action)
            {
                category = "Action";
            }
            else if (cat == Game::Strategy)
            {
                 category = "Strategy";
            }
            else if (cat == Game::Puzzle)
            {
                 category = "Puzzle";
            }
            else //(cat == App::Multimedia)
            {
                 category = "Platformer";
            }
            writer->writeStartElement("game");
            writer->writeAttribute("title", QString::fromStdString(game->getTitle()));
            writer->writeAttribute("developer", QString::fromStdString(game->getDeveloper()));
            writer->writeAttribute("rating", QString::number(game->getQuality()));
            writer->writeAttribute("nratings", QString::number(game->getRatings()));
            writer->writeAttribute("price", QString::number(game->getPrice()));
            writer->writeAttribute("xbox", QString::number(game->isXbox()));
            writer->writeAttribute("category", category);
            writer->writeEndElement();
        }
    }
    writer->writeEndElement();
    writer->writeEndDocument();
    delete writer;
}

void ContainerController::deserializeContainer(QString filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);

    QXmlStreamReader *reader = new QXmlStreamReader();
    reader->setDevice(&file);

    mainContainer = new container<SmartPointer>();

    while(!reader->atEnd() && !reader->hasError())
    {
        QXmlStreamReader::TokenType token = reader->readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (reader->name() == "items")
            {
                continue;
            }
            if (reader->name() == "app")
            {
                QXmlStreamAttributes attributes = reader->attributes();

                QString title = attributes.value("title").toString();
                QString developer = attributes.value("developer").toString();
                double rating = attributes.value("rating").toString().toDouble();
                int nratings = attributes.value("nratings").toString().toInt();
                double price = attributes.value("price").toString().toDouble();
                QString localization = attributes.value("localization").toString();
                QString category = attributes.value("category").toString();

                App::category cat;
                if (category == "Social")
                    cat = App::Social;
                else if (category == "Utility")
                    cat = App::Utility;
                else if (category == "News")
                    cat = App::News;
                else
                    cat = App::Multimedia;

                StoreItem *app = new App(title.toStdString(), developer.toStdString(), rating, nratings, cat, localization.toStdString(), price);
                mainContainer->push_back(app);
            }
            if (reader->name() == "game")
            {
                QXmlStreamAttributes attributes = reader->attributes();

                QString title = attributes.value("title").toString();
                QString developer = attributes.value("developer").toString();
                double rating = attributes.value("rating").toString().toDouble();
                int nratings = attributes.value("nratings").toString().toInt();
                double price = attributes.value("price").toString().toDouble();
                bool xbox = attributes.value("xbox").toString().toInt();
                QString category = attributes.value("category").toString();

                Game::category cat;
                if (category == "Puzzle")
                    cat = Game::Puzzle;
                else if (category == "Action")
                    cat = Game::Action;
                else if (category == "Strategy")
                    cat = Game::Strategy;
                else
                    cat = Game::Platformer;

                StoreItem *game = new Game(title.toStdString(), developer.toStdString(), rating, nratings, cat, price, xbox);
                mainContainer->push_back(game);
            }
        }
    }

    emit setLocalizationModel(this->getLocalizationModel());

    viewCont = new container<SmartPointer>(*mainContainer);
    updateView();
}
