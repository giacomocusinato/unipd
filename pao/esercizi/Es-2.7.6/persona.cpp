#include "persona.h"
#include <string>
#include <iostream>
using namespace std;

//Costruttori
Persona::Persona() 
	{ 
		Nome = ""; 
		Cognome = ""; 
		AnnoNascita = 0; 
		AnnoMorte = 0; 
	}
Persona::Persona(string nome, string cognome, int nascita, int morte)
	{
		Nome = nome;
		Cognome = cognome;
		AnnoNascita = nascita;
		AnnoMorte = morte;
	}
	
//Overloading cout
ostream& Persona::operator<<(ostream& os)
{
	return os << this->Nome << endl
						<< this->Cognome << endl
						<< this->AnnoNascita << endl
						<< this->AnnoMorte << endl;
}

