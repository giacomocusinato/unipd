#include "orario.h"
#include <iostream>
using namespace std;

orario::orario(int o, int m, int s)
{
    if(o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59)
        sec = 0;
    else
        sec = o * 3600 + m * 60 + s;
}

int orario::Ore() const { return sec / 3600; }
int orario::Minuti() const { return (sec / 60) % 60; }
int orario::Secondi() const { return sec % 60; }

bool orario::operator==(const orario& o) const
{
    return o.sec == sec;
}

ostream& operator<<(ostream& os, const orario& o)
{
    return os << o.Ore() << ":" << o.Minuti() << ":" << o.Secondi();
}
