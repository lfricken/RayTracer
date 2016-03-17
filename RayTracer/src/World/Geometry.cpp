#include "Geometry.hpp"
#include "Ray.hpp"
#include "World.hpp"
#include "Light.hpp"

using namespace leon;

Geometry::Geometry()
{
	color = sf::Color(128, 0, 128, 255);
	m_boxCalculated = false;
}
Geometry::~Geometry()
{

}
sf::Color Geometry::getColorPoint(const Vector& point, const World& world) const
{
	return color * world.lights[0]->getBrightness(point, getNormal(point), world);
}
/// <summary>
/// does this geometry intersect the specified ray?
/// </summary>
/// <param name="ray">The ray.</param>
/// <param name="world">The world.</param>
/// <returns>position of intersection</returns>
Vector Geometry::intersects(Ray& ray, const World& world) const
{
	Vector intersection = intersectsHook(ray, world);

	ray.lastHit = this;
	//if(!ray.onlyIntersection)
	//	if(intersection.init)///TODO fix only checking light 0
	//		ray.lastColor = getColorPoint(intersection, world);

	return intersection;
}
const BoundingBox& Geometry::getBoundBox() const
{
	if(!m_boxCalculated)
	{
		calcBoundBox();
		m_boxCalculated = true;
	}
	return m_box;
}
