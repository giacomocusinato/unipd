#include "telefonata.h"

telefonata::telefonata() { }

telefonata::telefonata(orario i, orario f, int n): inizio(i), fine(f), numero(n) { }

orario telefonata::Inizio() const { return inizio; }

orario telefonata::Fine() const { return fine; }

int telefonata::Numero() const { return numero; }

bool telefonata::operator==(const telefonata& t)
{
    return t.numero == numero && t.inizio == inizio && t.fine == fine;
}

ostream& operator<<(ostream& os, const telefonata& t)
{
    return os << "INIZIO: " << t.inizio << ", FINE: " << t.fine << ", NUMERO: " << t.numero;
}
