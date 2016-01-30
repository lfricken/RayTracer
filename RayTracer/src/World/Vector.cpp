#include "Vector.hpp"

using namespace leon;

Vector::Vector(double xi, double yi, double zi)
{
	x = xi;
	y = yi;
	z = zi;
}
Vector::~Vector()
{

}
double Vector::dot(const Vector& other) const
{
	return (x*other.x + y*other.y + z*other.z);
}