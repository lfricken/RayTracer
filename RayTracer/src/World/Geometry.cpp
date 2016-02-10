#include "Geometry.hpp"
#include "Ray.hpp"
#include "World.hpp"
#include "Light.hpp"

using namespace leon;

Geometry::Geometry()
{
	color = sf::Color(128, 0, 128, 255);
}
Geometry::~Geometry()
{

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

	if(intersection.init)///TODO fix only checking light 0
		ray.lastColor = color * world.lights[0]->getBrightness(intersection, getNormal(intersection), world);

	return intersection;
}
