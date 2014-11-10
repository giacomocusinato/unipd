#ifndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"
#include <iostream>
using std::ostream;

class bolletta
{
public:
    bolletta();
    bool Vuota() const;
    void Aggiungi_Telefonata(const telefonata&);
    void Togli_Telefonata(const telefonata&);
    telefonata Estrai_Una();
    friend ostream& operator<<(ostream& os, const bolletta& b);
private:
    class nodo;
    class smartp
    {
    public:
        nodo* punt;
        smartp(nodo* p=0); //COSTRUTTORE: agisce da convertitore implicito da nodo* a smartp, anche costr. senza argomenti
        smartp(const smartp&);
        ~smartp();
        smartp& operator=(const smartp&);
        nodo& operator*() const;
        nodo* operator->() const;
        bool operator==(const smartp&) const;
        bool operator!=(const smartp&) const;
    };
    class nodo
    {
    public:
        nodo();
        nodo(const telefonata&, const smartp&);
        telefonata info;
        smartp next;
        int riferimenti;
    };
    smartp first; //unico campo dati di bolletta
};

#endif // BOLLETTA_H
