//Esercizio 2.7.6 pag 40
#include <iostream>
#include "persona.h"
using namespace std;

int main()
{
	Persona pers = Persona("Napoleone", "Bonaparte", 1769, 1821);
	pers.operator<<(cout);
}
