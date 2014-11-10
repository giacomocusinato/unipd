#ifndef TELEFONATA_H
#define TELEFONATA_H
#include <iostream>
#include "orario.h"
using std::ostream;

class telefonata
{
public:
    telefonata();
    telefonata(orario, orario, int);
    orario Inizio() const;
    orario Fine() const;
    int Numero() const;
    bool operator==(const telefonata&);
    friend ostream& operator<<(ostream&, const telefonata&);
private:
    orario inizio, fine;
    int numero;
};

ostream& operator<<(ostream&, const telefonata&);

#endif // TELEFONATA_H
