#include <string>
using std::string;

class Nodo
{
	private:
		//Costruttore
		Nodo(string st="***", Nodo* s=0, Nodo* d=0): info(st), sx(s), dx(d) { }
		
		//Campi dati
		string info;
		Nodo* sx;
		Nodo* dx;
};

class Albero
{
	public:
		//Costruttore
		Albero(): radice(0) { }
		Albero(const Albero& t) //dichiarazione costruttore di copia
		{
			radice = copia(t.radice);
		}
		
		private:
			Nodo* radice;
			static Nodo* copia(Nodo* p)
			{
				if (!p)
					return 0;
				
				return new Nodo(p->info, copia(p->sx), copia(p->dx));
			}
};
