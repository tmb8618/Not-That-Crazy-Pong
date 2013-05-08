//TYLER BROGNA

#include "Vect.h"

Vect::Vect(void)
{
	x = 0;
	y = 0;
	z = 0;
}

Vect::Vect(int a, int b, int c)
{
	x = (float) a;
	y = (float) b;
	z = (float) c;
}

Vect::Vect(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vect::Vect(double a, double b, double c)
{
	x = (float) a;
	y = (float) b;
	z = (float) c;
}

Vect::Vect(const Vect& original)
{
	x = original.x;
	y = original.y;
	z = original.z;
}

Vect& Vect::operator + (const Vect& add)
{
	Vect toAdd;
	toAdd.x = x + add.x;
	toAdd.y = y + add.y;
	toAdd.z = z + add.z;
	return toAdd;
}

Vect& Vect::operator - (const Vect& sub)
{
	Vect toSub;
	toSub.x = x - sub.x;
	toSub.y = y - sub.y;
	toSub.z = z - sub.z;
	return toSub;
}

void Vect::operator = (const Vect& original)
{
	x = original.x;
	y = original.y;
	z = original.z;
}

Vect::~Vect(void)
{

}
