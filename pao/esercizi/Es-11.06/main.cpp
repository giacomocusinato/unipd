#include "Vettore.h"
#include <iostream>
using namespace std;

Vettore F(Vettore v)
{
	return v;
}

int main()
{
	Vettore v1 = Vettore(5, 0);
	Vettore v2 = Vettore(6, 0);
	
	v1 = v2;
	Vettore v3 = v1;
	
	F(v3);
	
	cout << v3;
}
