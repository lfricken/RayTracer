#include "Triangle.hpp"
#include "Ray.hpp"

using namespace leon;

Triangle::Triangle(Vector ai, Vector bi, Vector ci)
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
	double dot = rRay.dir.dot(normal);

	if(dot != 0)
	{

		return Vector();
	}
	else
		return Vector();
}

