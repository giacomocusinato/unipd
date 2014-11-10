/*Esercizio 2.7.5 pag 39*/
#include <iostream>
#include "point.h"
using namespace std;

void LanciaScelte(Point point);

int main()
{
	double a=0, b=0, c=0;
	
	cout << "Valore su asse X: " << endl;
	cin >> a;
	
	cout << "Valore su asse Y: " << endl;
	cin >> b;
	
	cout << "Valore su asse Z: " << endl;
	cin >> c;
	cout << endl << endl;
		
	Point point = Point(a, b, c);
	
	LanciaScelte(point);
	
	
}

void LanciaScelte(Point point)
{
	int scelta;
	cout << "1 - Trasforma nell'opposto." << endl << endl;
	cout << "2 - Trova la distanza del punto dall'origine." << endl << endl;
	cout << "3 - Stampa le coordinate del punto." << endl << endl;
	cout << "0 - Esci." << endl << endl;
	cin >> scelta;
	
	double dist;
	switch (scelta)
	{
		case 1: point.Negate(); point.Print(); cout << endl << endl; LanciaScelte(point);
				break;
		case 2: dist = point.Norm(); cout << dist << endl << endl; LanciaScelte(point);
				break;
		case 3: point.Print(); cout << endl << endl; LanciaScelte(point);
				break;
		case 0: return;
		default: cout << "Scelta errata." << endl << endl; LanciaScelte(point);
	}
}
