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
	const Vector norm = getNormal(point);

	const float sum = material.gloss + material.diffuse + material.specular + material.reflection;
	const float myFactor = (material.diffuse + material.specular) / sum;
	const float reflectFactor = material.reflection / sum;
	const float glossFactor = material.gloss / sum;

	sf::Color myColor = sf::Color::Yellow;
	sf::Color reflectColor = sf::Color::Magenta;
	sf::Color glossColor = sf::Color::White;

	if(material.diffuse + material.specular > 0)
	{
		Material textureMod = material;
		if(m_spTexture)
			textureMod.color = getTextureColor(point);

		myColor = world.lights[0]->getBrightness(ray, point, norm, world, textureMod);

	}
	if(material.reflection > 0)
	{
		const Vector rayDir = ray.dir;
		Ray reflectRay(point, rayDir.reflect(norm));
		reflectRay.ignore = this;
		world.getFirstHit(reflectRay);
		reflectColor = reflectRay.lastColor;

	}
	if(material.gloss > 0)
	{



	}
	{
		myColor.r *= myFactor;
		myColor.g *= myFactor;
		myColor.b *= myFactor;

		reflectColor.r *= reflectFactor;
		reflectColor.g *= reflectFactor;
		reflectColor.b *= reflectFactor;

		glossColor.r *= glossFactor;
		glossColor.g *= glossFactor;
		glossColor.b *= glossFactor;
	}

	auto my = sf::Color(myColor.r + reflectColor.r + glossColor.r, myColor.g + reflectColor.g + glossColor.g, myColor.b + reflectColor.b + glossColor.b);

	return my;
}
bool Geometry::intersects(Ray& ray, const World& world) const
{
	bool intersection = this->intersectsHook(ray, world);

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
sf::Color Geometry::getTextureColor(const Vector& hitPoint) const
{
	return m_spTexture->getPixel(400, 400);
}