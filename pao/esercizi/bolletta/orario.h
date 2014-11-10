#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
using std::ostream;

class orario
{
public:
    orario(int=0, int=0, int=0);
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    bool operator==(const orario&) const;
private:
    int sec;
};

ostream& operator<<(ostream&, const orario&);

#endif // ORARIO_H
