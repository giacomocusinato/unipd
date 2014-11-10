#ifndef RATINGLABEL_H
#define RATINGLABEL_H

#include <QLabel>
#include <QImage>

class RatingLabel : public QLabel
{
private:
    double rating;
    QImage star;
    QImage emptystar;
    QImage halfstar;
public:
    RatingLabel(double=0);
    void paintEvent(QPaintEvent *);
};

#endif // RATINGLABEL_H
