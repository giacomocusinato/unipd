#ifndef ADDNEWGAME_H
#define ADDNEWGAME_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QCheckBox>

#include "game.h"

class AddGameView : public QWidget
{
    Q_OBJECT
public:
    explicit AddGameView(QWidget *parent = 0);
 private:
    QLineEdit *titleEdit;
    QLineEdit *devEdit;
    QDoubleSpinBox *ratingEdit;
    QDoubleSpinBox *priceEdit;
    QSpinBox *nratingEdit;
    QCheckBox *puzzleCheck;
    QCheckBox *strategyCheck;
    QCheckBox *platformerCheck;
    QCheckBox *actionCheck;
    QCheckBox *indieCheck;
    QCheckBox *xboxCheck;
signals:
    void newGameAdded(Game) const;
public slots:
    void manageNewData();
    
};

#endif // ADDNEWGAME_H
