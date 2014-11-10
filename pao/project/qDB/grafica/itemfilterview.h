#ifndef ITEMFILTERVIEW_H
#define ITEMFILTERVIEW_H

#include <QWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QString>
#include <QPushButton>
#include <QHash>
#include <QStringListModel>
#include <QListView>

class ItemFilterView : public QWidget
{
    Q_OBJECT
public:
    explicit ItemFilterView(QStringListModel *model, QWidget *parent = 0);
private:
    QStringListModel *localizationModel;
    QListView *localizationView;

    QCheckBox *freeAppCheckBox;
    QCheckBox *paidAppCheckBox;
    QCheckBox *socialCheckBox;
    QCheckBox *newsCheckBox;
    QCheckBox *multimediaCheckBox;
    QCheckBox *utilityCheckBox;

    QCheckBox *freeGameCheckBox;
    QCheckBox *paidGameCheckBox;
    QCheckBox *puzzleCheckBox;
    QCheckBox *actionCheckBox;
    QCheckBox *platformerCheckBox;
    QCheckBox *strategyCheckBox;
    QCheckBox *xboxCheckBox;
    QCheckBox *indieCheckBox;

    static QString groupBoxStyle;

signals:
    void filterChanged(QHash<QString, int>) const;
public slots:
    void filterManager() const;
    void updateData() const;
    void updateLocalizationModel(QString);
    void setLocalizationModel(QStringListModel*);
};

#endif // ITEMFILTERVIEW_H
