#include "Plane.hpp"
#include "Ray.hpp"

using namespace leon;

Plane::Plane(Vector pointi, Vector normali)
{
	point = pointi;
	point.w = 1;
	normal = normali.normal();
	normal.w = 0;
}
Plane::~Plane()
{

}
/// <summary>
/// Intersectses the hook.
/// </summary>
/// <param name="rRay">The r ray.</param>
/// <param name="world">The world.</param>
/// <returns></returns>
Vector Plane::intersectsHook(Ray& rRay, const World& world) const
{
	double dot = rRay.dir.dot(normal);

	if(dot != 0)
	{
		double t = ((point - rRay.pos).dot(normal)) / dot;
		if(t > 0)
		{
			rRay.time = t;
			Vector hitPoint = rRay.getFuture(t);
			hitPoint.init = true;
			return hitPoint;
		}
		else
			return Vector();
	}
	else
		return Vector();
}
/// <summary>
/// Gets the normal.
/// </summary>
/// <param name="point">The point.</param>
/// <returns></returns>
Vector Plane::getNormal(const Vector& point) const
{
	return normal;
}
/// <summary>
/// Translates the specified dist.
/// </summary>
/// <param name="dist">The dist.</param>
void Plane::translate(const Vector& dist)
{
	point = point + dist;
}
/// <summary>
/// Transforms the specified rot.
/// </summary>
/// <param name="rot">The rot.</param>
void Plane::transform(const Matrix& rot)
{
	point = rot*point;
	normal = (rot*normal).normal();
	normal.w = 0;
}
void Plane::calcBoundBox() const
{

}


