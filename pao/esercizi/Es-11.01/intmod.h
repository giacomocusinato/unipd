#ifndef INTMOD.H
#define INTMOD.H

class IntMod
{
	public:
		explicit IntMod(int n=0); // impedisce la conversione escplicita int->IntMod
		operator int() const;     // conversione implicita IntMod->int		
		IntMod operator+(const IntMod&) const;
		IntMod operator*(const IntMod&) const;
		static void setModulo(int);
	
	private:
		static int modulo;
		int val;
}

#endif
