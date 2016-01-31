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

		b0 = p.area(a, b) / area;
		b1 = p.area(b, c) / area;
		b2 = p.area(c, a) / area;
		if((b0 >= 0 && b0 <= 1) && (b1 >= 0 && b1 <= 1) && (b2 >= 0 && b2 <= 1))
			return p;
		else
			return Vector();
	}
	else
		return Vector();
}