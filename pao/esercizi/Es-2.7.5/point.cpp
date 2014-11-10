#include <iostream>
#include <math.h>
#include "point.h"
using std::cout;
using std::endl;

//Costruttori
Point::Point() { Point::X = 0; Point::Y = 0; Point::Z = 0; }
Point::Point(double a) { Point::X = a; Point::Y = 0; Point::Z = 0; }
Point::Point(double a, double b) { Point::X = a; Point::Y = b; Point::Z = 0; }
Point::Point(double a, double b , double c) { Point::X = a; Point::Y = b; Point::Z = c; }

void Point::Negate()
{
	this->X = -(this->X);
	this->Y = -(this->Y);
	this->Z = -(this->Z);
}

double Point::Norm()
{
	double x = pow(this->X, 2.0);
	double y = pow(this->Y, 2.0);
	double z = pow(this->Z, 2.0);
	double dist = sqrt(x + y + z);
	
	return dist;
}
 
void Point::Print()
{
	cout << this->X << " " << this->Y << " " << this->Z << endl;
}

