#ifndef VETTORE_H
#define VETTORE_H

#include <iostream>
using std::ostream;

class Vettore
{
	friend ostream& operator<<(ostream&, const Vettore&); 
	
	public:
		Vettore(int =1, int =0);
		Vettore(const Vettore&);
		Vettore& operator=(const Vettore&);
		int& operator[] (int) const;
		bool operator==(const Vettore&) const;
		int dim() { return size; }
				
	private:
		int size; //dimensione vettore		
		int* v;   //puntatore all'array dinamico
};

ostream& operator<<(ostream&, const Vettore&);

#endif
