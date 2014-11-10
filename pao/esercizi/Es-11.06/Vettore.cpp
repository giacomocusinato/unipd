#include "Vettore.h"
#include <iostream>
using namespace std;

Vettore::Vettore(int dim, int value): size(dim), v(new int[dim])
{
	for(int i=0; i<dim; i++)
		v[i] = value;
}

Vettore::Vettore(const Vettore& x): size(x.size), v(new int[x.size])
{
	for(int i=0; i<size; i++)
	{
		v[i] = x.v[i];
	}
	
	cout << "Usato costruttore di copia" << endl;
}

Vettore& Vettore::operator=(const Vettore& x)
{
	if(this == &x)
		return *this;
	delete [] v;
	v = new int[x.size];
	for(int i=0; i<x.size; i++)
		v[i] = x.v[i];
		
	cout << "Usato operatore assegnazione" << endl;
}

int& Vettore::operator[] (int i) const
{
	return v[i];
}

bool Vettore::operator==(const Vettore& x) const
{
	if (size != x.size)
		return false;
	for (int i=0; i<size; i++)
	{
		if(x.v[i] != v[i])
			return false;
	}
	return true;		
}

ostream& operator<<(ostream& os, const Vettore& x)
{
	for (int i=0; i<x.size; i++)
	{
		os << x[i] << " ";
	}
	os << endl;
	
	return os;
}






