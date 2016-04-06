#include "Geometry.hpp"
#include "Ray.hpp"
#include "World.hpp"
#include "Light.hpp"

using namespace leon;

Geometry::Geometry()
{
	material.color = sf::Color(128, 0, 128, 255);
	m_boxCalculated = false;
}
Geometry::~Geometry()
{

}
sf::Color Geometry::getColorPoint(const Vector& point, const World& world) const
{
	Light& light = *world.lights[0];
	return light.getBrightness(point, getNormal(point), world, material);
}
Vector Geometry::intersects(Ray& ray, const World& world) const
{
	Vector intersection = intersectsHook(ray, world);

	ray.lastHit = this;

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
