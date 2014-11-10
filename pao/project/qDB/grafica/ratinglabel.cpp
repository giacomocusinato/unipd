#include <QPainter>

#include "ratinglabel.h"


RatingLabel::RatingLabel(double r) :
    rating(r)
{
    this->setFixedSize(100, 20);

    star = QImage(":/Stars/Resources/Stars/star.png");
    halfstar = QImage(":/Stars/Resources/Stars/halfstar.png");
    emptystar = QImage(":/Stars/Resources/Stars/emptystar.png");
}

void RatingLabel::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int nstar = 0;
    int nhalf = 0;
    int nempty = 0;

    // Rating as halfstars ony
    for (double n=rating; n>=0.5; n-=0.5)
        nhalf++;
    if (0 < rating && rating < 0.5)
        nhalf = 1;

    nstar = nhalf / 2;
    nhalf = nhalf % 2;
    nempty = 5 - (nstar + nhalf);

    int i = 0;
    for (; nstar>0; nstar--)
    {
        painter.drawImage(QRectF(i*20, 0, 20, 20), star, QRectF(0, 0, 20, 20));
        ++i;
    }
    for (; nhalf>0; nhalf--)
    {
        painter.drawImage(QRectF(i*20, 0, 20, 20), halfstar, QRectF(0, 0, 20, 20));
        ++i;
    }
    for (; nempty>0; nempty--)
    {
        painter.drawImage(QRectF(i*20, 0, 20, 20), emptystar, QRectF(0, 0, 20, 20));
        ++i;
    }
}
