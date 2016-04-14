#include "Vector.hpp"
#include "stdafx.hpp"

using namespace leon;

Vector::Vector()
{
	init = false;
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}
Vector::Vector(double xi, double yi, double zi, double wi)
{
	init = true;
	x = xi;
	y = yi;
	z = zi;
	w = wi;
}
Vector::~Vector()
{

}
Vector Vector::inv() const
{
	return Vector(-x, -y, -z);
}
double Vector::area(const Vector& b, const Vector& c) const
{
	Vector ab = this->to(b);
	Vector ac = this->to(c);

	return ab.cross(ac).len()/2;
}
Vector Vector::reflect(const Vector& other) const//reflect this across other
{
	return (*this - other*(2 * this->dot(other)));
}
double Vector::dot(const Vector& other) const
{
	return (x*other.x + y*other.y + z*other.z);
}
Vector Vector::cross(const Vector& other) const//cross product
{
	return Vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}
double Vector::dist(const Vector& other) const
{
	double dx, dy, dz;
	dx = x - other.x;
	dy = y - other.y;
	dz = z - other.z;
		
	return sqrt(dx*dx + dy*dy + dz*dz);
}
double Vector::len() const
{
	return sqrt(x*x + y*y + z*z);
}
Vector Vector::normal() const//return a vector that is normalized
{
	return Vector(x,y,z) / len();
}
void Vector::normalize()//normalize this vector
{
	*this = Vector(x, y, z) / len();
}
Vector Vector::to(const Vector& other) const
{
	return Vector(other.x-x, other.y-y, other.z-z);
}
/**OPERATOR OVERLOAD**/
Vector Vector::operator-(const Vector& other) const
{
	return Vector(x - other.x, y - other.y, z - other.z);
}
Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.x, y + other.y, z + other.z);
}
Vector Vector::operator*(double c) const
{
	return Vector(x*c, y*c, z*c);
}
Vector Vector::operator/(double c) const
{
	return Vector(x/c, y/c, z/c);
}
bool Vector::operator!=(const Vector& other) const
{
	return (x != other.x || y != other.y || z != other.z);
}

