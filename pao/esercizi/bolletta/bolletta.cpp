#include "bolletta.h"
using std::ostream; using std::endl;

//METODI DI smartp

bolletta::smartp::smartp(nodo* p): punt(p) { if (punt) punt->riferimenti++; } // costruttore

bolletta::smartp::smartp(const smartp& s): punt(s.punt) { if (punt) punt->riferimenti++; } // costruttore copia

bolletta::smartp::~smartp() //distruttore
{
    if (punt)
        punt->riferimenti--;
    if (punt->riferimenti == 0)
        delete punt;
            //NB: il delete standard di nodo richiama ricorsivamente il distruttore di smartp
}

bolletta::smartp& bolletta::smartp::operator=(const smartp& s)
{
    if(this != &s)
    {
        nodo* t = punt;
        // if(t) punt->riferimenti++;
        // if(punt) punt->riferimenti--;
        punt = s.punt;
        if (punt) punt->riferimenti++;
        if (t)
            t->riferimenti--;
        if (t->riferimenti == 0)
            delete t; // delete standard di nodo che richiama il distruttore ridefinito di smartp
    }
    return *this;
}

bolletta::nodo& bolletta::smartp::operator *() const { return *punt; } // trasforma smartp s nello l-valore di nodo puntato da s.punt

bolletta::nodo* bolletta::smartp::operator ->() const { return punt; } // trasforma un oggetto s di smartp ne puntatore ordinario a nodo contenuto in smartp

bool bolletta::smartp::operator==(const smartp& p) const { return punt == p.punt; }

bool bolletta::smartp::operator!=(const smartp& p) const { return punt != p.punt; }


// METODI DI nodo

bolletta::nodo::nodo(): riferimenti(0) { } // NB: invocazioni info() e next() implicite

bolletta::nodo::nodo(const telefonata& t, const smartp& p): info(t), next(p), riferimenti(0) { }
        // NB: next(p) è un'invocazione al costruttore di copia ridefinito smartp


// METODI DI bolletta

bolletta::bolletta() { }

bool bolletta::Vuota() const { return first == 0; } //Cast implicito 0 => smartp

void bolletta::Aggiungi_Telefonata(const telefonata& t)
{
    first = new nodo(t, first); //Cast implicito da nodo* a smartp
}

telefonata bolletta::Estrai_Una()
{
    if (this->Vuota())
        return telefonata(0,0,0);

    telefonata aux = first->info;
    first = first->next;
    return aux;
}

void bolletta::Togli_Telefonata(const telefonata& t)
{
    smartp p = first, prec, q;
    smartp original = first; // first originale
    first = 0;
    // p scorre la lista, prec è il nodo che precede quello puntato da p, q punta alla copia del nodo
    while (p!=0 && !(p->info == t)) // p è uno smartp quindi notare il p!=0
    {
        // fa una copia dei nodi che precede, eventualmente quello da togliere
        q = new nodo(p->info, p->next);
        // e li inserisce nalla nuova lsita puntata da first
        if (prec == 0)
            first = q;
        else
            prec->next = q;
        // aggiorna prec e p per il ciclo while
        prec = q;
        p = p->next;
    }
    // se p=0 la telefonata non è stata trovata, ho inutilmente copiato la lista quindi ripristino la situazione originale
    if (p==0)
        first = original;
    else if (prec == 0)
        first = p->next; // t era in testa
    else
        prec->next = p->next; // le variabili locali p, q, prec vengono distrutte
}

ostream& operator<<(ostream& os, const bolletta& b)
{
    if (b.Vuota())
        os << "BOLLETTA VUOTA" << endl;
    else
    {
        os << "TELEFONATE IN BOLLETTA" << endl;
        bolletta::smartp p = b.first; // amicizia
        int i = 1;
        while (p!=0)
        {
            return os << i++ << ") " << p->info << endl;
            p->next;
        }
    }

}
