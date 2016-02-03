#include "Triangle.hpp"
#include "Ray.hpp"
#include "Plane.hpp"

using namespace leon;

Triangle::Triangle(Vector ai, Vector bi, Vector ci) : plane(ai, (ai.to(bi).cross(ai.to(ci))))
{
	a = ai;
	b = bi;
	c = ci;
}
Triangle::~Triangle()
{

}
Vector Triangle::intersectsHook(Ray& rRay, const World& world) const
{
	double dot = rRay.dir.dot(plane.normal);

	if(dot != 0)
	{
		Vector p = plane.intersects(rRay, world);

		Vector a1 = p.to(a);
		Vector a2 = p.to(b);
		Vector a3 = a1.cross(a2);
		double sidea = a3.dot(plane.normal);

		Vector b1 = p.to(b);
		Vector b2 = p.to(c);
		Vector b3 = b1.cross(b2);
		double sideb = b3.dot(plane.normal);

		Vector c1 = p.to(c);
		Vector c2 = p.to(a);
		Vector c3 = c1.cross(c2);
		double sidec = c3.dot(plane.normal);

		if(sidea >= 0 && sideb >= 0 && sidec >= 0)
			return p;
		else
			return Vector();
	}
	else
		return Vector();
}
Vector Triangle::getNormal(const Vector& point) const
{
	return plane.normal;
}
void Triangle::translate(const Vector& dist)
{
	a = a + dist;
	b = b + dist;
	c = c + dist;
}
void Triangle::transform(const Matrix& rot)
{
	a = rot*a;
	b = rot*b;
	c = rot*c;
}
