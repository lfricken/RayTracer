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
	const int recursionLimit = 1;

	const Vector norm = getNormal(point);

	float glossLimit = material.gloss;
	float reflectLimit = material.reflection;
	if(ray.recursion >= recursionLimit)
	{
		reflectLimit = 0;
		glossLimit = 0;
	}


	const float sum = glossLimit + material.diffuse + material.specular + reflectLimit;
	const float myFactor = (material.diffuse + material.specular) / sum;
	const float reflectFactor = reflectLimit / sum;
	const float glossFactor = glossLimit / sum;


	sf::Color myColor = sf::Color::Yellow;
	sf::Color reflectColor = sf::Color::Magenta;
	sf::Color glossColor = sf::Color::White;
	sf::Color transColor = sf::Color::Green;

	if(material.diffuse + material.specular > 0)
	{
		Material textureMod = material;
		if(m_spTexture)
			textureMod.color = getTextureColor(point);

		myColor = world.lights[0]->getBrightness(ray, point, norm, world, textureMod);
	}
	if(reflectLimit > 0)
	{
		Ray reflectRay(point, ray.dir.reflect(norm));
		reflectRay.ignore = this;
		reflectRay.recursion = ray.recursion + 1;
		world.getFirstHit(reflectRay);
		reflectColor = reflectRay.lastColor;

	}
	if(glossLimit > 0)
	{
		Vector reflectionDir = ray.dir.reflect(norm);
		Vector axisA = Vector(1, 0, 0).cross(reflectionDir).normal()*material.glossRootDimensions;
		Vector axisB = axisA.cross(reflectionDir).normal()*material.glossRootDimensions;
		Vector pos = point + reflectionDir - (axisA / 2) - (axisB / 2);
		Vector sample;
		int m_rootSamples = material.glossRootSamples;
		int r = 0, g = 0, b = 0;

		for(int i = 0; i <= m_rootSamples; ++i)
		{
			float fracA = static_cast<float>(i) / static_cast<float>(m_rootSamples);//calculate fractions
			for(int j = 0; j <= m_rootSamples; ++j)
			{
				float fracB = static_cast<float>(j) / static_cast<float>(m_rootSamples);//calculate fractions

				sample = pos + (axisA*fracA) + (axisB*fracB);

				Ray reflectRay(point, point.to(sample));
				reflectRay.ignore = this;
				reflectRay.recursion = ray.recursion + 1;
				world.getFirstHit(reflectRay);
				sf::Color singleHit = reflectRay.lastColor;

				r += singleHit.r;
				g += singleHit.g;
				b += singleHit.b;
			}
		}

		int totalSamples = (m_rootSamples + 1)*(m_rootSamples + 1);
		glossColor = sf::Color(r / totalSamples, g / totalSamples, b / totalSamples);
	}
	if(material.transparency > 0)
	{
		//Vector dir = norm.inv();

		//auto thetaI = norm.angle(dir);
		//auto w0 = ray.dir.inv();
		//auto snell = 1 / material.indexRefraction;

		//Vector t = w0*snell - norm.dot(snell*std::cos(thetaI));

		Ray reflectRay(point, norm.inv());
		reflectRay.ignore = this;
		reflectRay.recursion = ray.recursion;
		world.getFirstHit(reflectRay);
		transColor = reflectRay.lastColor;
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

		transColor.r *= material.transparency;
		transColor.g *= material.transparency;
		transColor.b *= material.transparency;
	}

	//auto my = sf::Color(myColor.r + reflectColor.r + glossColor.r + transColor.r, myColor.g + reflectColor.g + glossColor.g + transColor.g, myColor.b + reflectColor.b + glossColor.b + transColor.b);
	auto my = myColor + reflectColor + glossColor;

	if(material.transparency > 0)
	{
		auto realFactor = 1 - material.transparency;

		my.r *= realFactor;
		my.g *= realFactor;
		my.b *= realFactor;

		my = transColor + my;
	}

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