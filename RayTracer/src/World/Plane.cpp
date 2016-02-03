#include "Plane.hpp"
#include "Ray.hpp"

using namespace leon;

Plane::Plane(Vector pointi, Vector normali)
{
	point = pointi;
	normal = normali;
}
Plane::~Plane()
{

}
Vector Plane::intersectsHook(Ray& rRay, const World& world) const
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
Vector Plane::getNormal(const Vector& point) const
{
	return normal;
}
