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
Vector Triangle::intersects(Ray& rRay) const
{
	double dot = rRay.dir.dot(plane.normal);

	if(dot != 0)
	{
		double area, b0, b1, b2;
		Vector p = plane.intersects(rRay);
		area = a.area(b, c);

		double total = p.area(a, b);
		total += p.area(b, c);
		total += p.area(c, a);
		if(total <= area)
			return p;
		else
			return Vector();
	}
	else
		return Vector();
}