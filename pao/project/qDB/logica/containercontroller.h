#ifndef CONTAINERCONTROLLER_H
#define CONTAINERCONTROLLER_H

#include <QStringList>
#include <QStringListModel>

#include "containermodel.h"
#include "containerview.h"
#include "itemeditor.h"
#include "app.h"
#include "game.h"

class ContainerController : public QObject
{
    Q_OBJECT

public:
    ContainerController(ContainerModel*, ContainerView*);

    void updateView();
    QStringListModel *getLocalizationModel() const;

    inline void showView() const { view->show(); }
    inline container<SmartPointer>* getCont() { return mainContainer; }
private:
    ContainerModel *model;
    ContainerView *view;
    container<SmartPointer> *mainContainer;
    container<SmartPointer> *viewCont;
    QHash<QString,int> *filter;

    bool checkItemCategory(const StoreItem *item) const;
public slots:
    void manageViewItems(QHash<QString, int>);
    void editIndex(QModelIndex);
    void modifyItem(QStringList, QString);
    void addNewApp(App);
    void addNewGame(Game);
    void serializeContainer(QString) const;
    void deserializeContainer(QString);
signals:
    void updateData();
    void setLocalizationModel(QStringListModel*);
};

#endif // CONTAINERCONTROLLER_H
