#include <string>
#include <iostream>
using namespace std;

class Persona
{
	public:
		Persona();
		Persona(string, string, int, int);
		
		string Nome;
		string Cognome;
		int AnnoNascita;
		int AnnoMorte;
		
		ostream& operator<<(ostream&);
};
