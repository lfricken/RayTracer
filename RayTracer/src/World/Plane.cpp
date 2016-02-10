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
		rRay.time = t;
		return rRay.getFuture(t);
	}
	else
		return Vector();
}
Vector Plane::getNormal(const Vector& point) const
{
	return normal;
}
void Plane::translate(const Vector& dist)
{
	point = point + dist;
}
void Plane::transform(const Matrix& rot)
{
	point = rot*point;
	normal = rot*normal;
}

