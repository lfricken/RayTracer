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
/// <summary>
/// Hooked function for a ray that is intersecting us
/// </summary>
/// <param name="rRay">the ray.</param>
/// <param name="world">the world.</param>
/// <returns></returns>
Vector Triangle::intersectsHook(Ray& rRay, const World& world) const
{
	//time of intersection set in plane
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
/// <summary>
/// Gets the normal to this triangle.
/// </summary>
/// <param name="point">unnused</param>
/// <returns></returns>
Vector Triangle::getNormal(const Vector& point) const
{
	return plane.normal;
}
/// <summary>
/// Translates the specified distance.
/// </summary>
/// <param name="dist">The dist.</param>
void Triangle::translate(const Vector& dist)
{
	a = a + dist;
	b = b + dist;
	c = c + dist;

	plane = Plane(a, (a.to(b).cross(a.to(c))));
}
/// <summary>
/// Transforms the specified rotation.
/// </summary>
/// <param name="rot">The rot.</param>
void Triangle::transform(const Matrix& rot)
{
	a = rot*a;
	b = rot*b;
	c = rot*c;

	plane = Plane(a, (a.to(b).cross(a.to(c))));
}
void Triangle::calcBoundBox() const
{
	m_box.min.x = min3(a.x, b.x, c.x);
	m_box.min.y = min3(a.y, b.y, c.y);
	m_box.min.z = min3(a.z, b.z, c.z);

	m_box.max.x = max3(a.x, b.x, c.x);
	m_box.max.y = max3(a.y, b.y, c.y);
	m_box.max.z = max3(a.z, b.z, c.z);
}

