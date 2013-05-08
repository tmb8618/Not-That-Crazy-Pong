#pragma once
class Vect
{
public:
	
	float x;
	float y;
	float z;

	Vect();
	Vect(int, int, int);
	Vect(float, float, float);
	Vect(double, double, double);

	Vect(const Vect& original);

	Vect& operator + (const Vect& add);
	Vect& operator - (const Vect& sub);
	Vect& operator * (const float& mult);
	Vect& operator / (const float& div);

	float& Dot(const Vect& one, const Vect& two);
	Vect& Cross(const Vect& one, const Vect& two);

	void operator = (const Vect& original);

	~Vect(void);
};

