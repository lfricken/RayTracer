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
sf::Color Geometry::getColorPoint(const Ray& ray, const Vector& point, const World& world) const
{
	const Vector rayDir = ray.dir;
	const Vector norm = getNormal(point);

	Light& light = *world.lights[0];

	const float m = 1 - material.reflection;
	const float r = material.reflection;

	sf::Color reflectedColor = sf::Color::Magenta;
	sf::Color myColor = light.getBrightness(ray, point, norm, world, material);

	if(material.reflection > 0)
	{
		//if(ray.dir.z < -0.15 && ray.dir.z > -0.2)
		//	myColor = sf::Color::Red;

		Ray reflectRay(point, rayDir.reflect(norm));
		reflectRay.ignore = this;
		world.getFirstHit(reflectRay);
		reflectedColor = reflectRay.lastColor;
	}


	return sf::Color(myColor.r * m + reflectedColor.r * r, myColor.g * m + reflectedColor.g * r, myColor.b * m + reflectedColor.b * r);
}
Vector Geometry::intersects(Ray& ray, const World& world) const
{
	Vector intersection = this->intersectsHook(ray, world);

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
