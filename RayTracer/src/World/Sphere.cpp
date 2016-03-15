#include "Sphere.hpp"
#include "Ray.hpp"

using namespace leon;

Sphere::Sphere(Vector position, double radiusi)
{
	pos = position;
	radius = radiusi;
}
Sphere::~Sphere()
{

}
/// <summary>
/// hook function for ray intersection
/// </summary>
/// <param name="rRay">the ray.</param>
/// <param name="world">The world.</param>
/// <returns></returns>
Vector Sphere::intersectsHook(Ray& rRay, const World& world) const
{
	double a = rRay.dir.dot(rRay.dir);
	double b = (2 * ((rRay.pos - pos).dot(rRay.dir)));
	double c = (rRay.pos - pos).dot(rRay.pos - pos) - (radius*radius);

	double underRoot = (b*b) - (4 * a * c);

	if(underRoot >= 0)
	{
		double t = (-b + sqrt(underRoot)) / (2 * a);
		double t2 = (-b - sqrt(underRoot)) / (2 * a);

		if(t < 0 && t2 < 0)//are they both negative times?
			return Vector();
		if(t2 >= 0 && t2 < t)//is the second time smaller and non negative?
			t = t2;

		rRay.time = t;
		return rRay.getFuture(t);
	}

	return Vector();
}
/// <summary>
/// Gets the normal for a point on the sphere.
/// </summary>
/// <param name="point">The point.</param>
/// <returns></returns>
Vector Sphere::getNormal(const Vector& point) const
{
	return pos.to(point).normal();
}
/// <summary>
/// Translates the specified distance.
/// </summary>
/// <param name="dist">The dist.</param>
void Sphere::translate(const Vector& dist)
{
	pos = pos + dist;
}
/// <summary>
/// Transforms the specified rotation.
/// </summary>
/// <param name="rot">The rot.</param>
void Sphere::transform(const Matrix& rot)
{
	pos = rot*pos;
}
void Sphere::calcBoundBox() const
{
	m_box = BoundingBox(pos, radius);
}
