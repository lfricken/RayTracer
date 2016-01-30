#include "Plane.hpp"
#include "Ray.hpp"

using namespace leon;

Plane::Plane()
{

}
Plane::~Plane()
{

}
Vector Plane::intersects(Ray& rRay) const
{
	double dot = rRay.dir.dot(normal);

	if(dot != 0)
	{
		double t = ((point - rRay.pos).dot(normal)) / dot;
		return rRay.getFuture(t);
	}
	else
		return Vector();
}