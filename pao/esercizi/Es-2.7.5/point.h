//Interfaccia Point
class Point
{
	public:
		Point();
		Point(double);
		Point(double, double);
		Point(double, double, double);
		double X;
		double Y;
		double Z;
		
		void Negate();
		double Norm();
		void Print();
};
