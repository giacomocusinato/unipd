#include <QHBoxLayout>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>

#include "mainwindow.h"
#include "addappview.h"
#include "addgameview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ContainerView *view = new ContainerView();
    ContainerController *controller = new ContainerController(new ContainerModel(0), view);
    ItemFilterView *filterview = new ItemFilterView(controller->getLocalizationModel());

    connect(filterview, SIGNAL(filterChanged(QHash<QString,int>)), controller, SLOT(manageViewItems(QHash<QString,int>)));
    connect(controller, SIGNAL(updateData()), filterview, SLOT(updateData()));
    connect(controller, SIGNAL(setLocalizationModel(QStringListModel*)), filterview, SLOT(setLocalizationModel(QStringListModel*)));


    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(view);
    layout->addWidget(filterview);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    QMenu* menu = menuBar()->addMenu("File");
    QAction *action1 = menu->addAction("Add App");
    QAction *action2 = menu->addAction("Add Game");
    QAction *action3 = menu->addAction("Open");
    QAction *action4 = menu->addAction("Save");


    AddAppView *addapp = new AddAppView();
    AddGameView *addgame = new AddGameView();

    connect(action1, SIGNAL(triggered()), addapp, SLOT(show()));
    connect(action2, SIGNAL(triggered()), addgame, SLOT(show()));
    connect(addapp, SIGNAL(newAppAdded(App)), controller, SLOT(addNewApp(App)));
    connect(addgame, SIGNAL(newGameAdded(Game)), controller, SLOT(addNewGame(Game)));
    connect(addapp, SIGNAL(updateLocalizationList(QString)), filterview, SLOT(updateLocalizationModel(QString)));


    QFileDialog *openFileDialog = new QFileDialog();
    openFileDialog->setNameFilter("*.xml");
    QFileDialog *saveFileDialog = new QFileDialog();
    saveFileDialog->setNameFilter("*.xml");
    saveFileDialog->setAcceptMode(QFileDialog::AcceptSave);

    connect(action3, SIGNAL(triggered()), openFileDialog, SLOT(show()));
    connect(action4,SIGNAL(triggered()), saveFileDialog, SLOT(show()));
    connect(openFileDialog, SIGNAL(fileSelected(QString)), controller, SLOT(deserializeContainer(QString)));
    connect(saveFileDialog, SIGNAL(fileSelected(QString)), controller, SLOT(serializeContainer(QString)));
}
