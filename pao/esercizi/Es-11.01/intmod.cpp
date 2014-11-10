		
explicit intMod::IntMod(int n) : val(n%modulo) // impedisce la conversione escplicita int->IntMod

static void IntMod::setModulo(int mod) { modulo = mod; }

operator int() const     // conversione implicita IntMod->int		
{
	return val;
}

IntMod IntMod::operator+(const IntMod& a) const
{
	return IntMod(val + a.val);
}

IntMod IntMod::operator*(const IntMod&) const
{
	return IntMod(val * a.val);
}
