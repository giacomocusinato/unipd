#ifndef ADDAPPVIEW_H
#define ADDAPPVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QString>

#include "app.h"

class AddAppView : public QWidget
{
    Q_OBJECT
public:
    explicit AddAppView(QWidget *parent = 0);
private:
    QLineEdit *titleEdit;
    QLineEdit *devEdit;
    QDoubleSpinBox *ratingEdit;
    QDoubleSpinBox *priceEdit;
    QSpinBox *nratingEdit;
    QLineEdit *localizationEdit;
    QCheckBox *newsCheck;
    QCheckBox *socialCheck;
    QCheckBox *utilityCheck;
    QCheckBox *multimediaCheck;
signals:
    void newAppAdded(App) const;
    void updateLocalizationList(QString);
public slots:
    void manageNewData();
};

#endif // ADDAPPVIEW_H
