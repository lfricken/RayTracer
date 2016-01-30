#include "Triangle.hpp"
#include "Ray.hpp"

using namespace leon;

Triangle::Triangle()
{

}
Triangle::~Triangle()
{

}
bool Triangle::intersects(Ray& rRay) const
{
	double cross = rRay.dir.dot(normal);

	//else
		return false;
}