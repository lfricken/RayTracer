#include "Light.hpp"
#include "World.hpp"
#include "Ray.hpp"

#include <algorithm>
#include "Material.hpp"

using namespace leon;
using namespace std;

Light::Light(const sf::Color& colori)
{
	color = colori;
}
Light::~Light()
{

}
/// <summary>
/// Gets the brightness for a point in the world, with a surface normal.
/// </summary>
/// <param name="point">The point.</param>
/// <param name="normal">The normal.</param>
/// <param name="world">The world.</param>
/// <returns>color at that spot</returns>
sf::Color Light::getBrightness(const Ray& ray, const Vector& point, const Vector& normal, const World& world, const Material& material) const
{
	const Vector direction = this->getDirection(point);
	const sf::Color& ambient = world.ambientLight;


	if(!inShadow(point, world))
	{
		const int diffValue = getDiffuse(point, normal, world, direction);
		const float diffFrac = material.diffuse*static_cast<float>(diffValue) / 255.f;
		const sf::Color diffuse = material.color * sf::Color(diffFrac * color.r, diffFrac * color.g, diffFrac * color.b);

		//if(diffValue < 0)
		//	return ambient;

		const int specValue = getSpecular(ray, point, normal, world, direction);
		const float specFrac = material.specular*static_cast<float>(specValue) / 255.f;
		const sf::Color specular = sf::Color::White * sf::Color(specFrac * color.r, specFrac * color.g, specFrac * color.b);

		return sf::Color(std::min(255, diffuse.r + specular.r + ambient.r), std::min(255, diffuse.g + specular.g + ambient.g), std::min(255, diffuse.b + specular.b + ambient.b));
	}
	else
		return ambient;
}
int Light::getSpecular(const Ray& ray, const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	const Vector rayDirInv = ray.dir.inv();

	const Vector p = point.normal();
	const Vector n = normal.normal();
	const Vector l = lightRayDir.normal();

	const Vector reflectionRay = l.reflect(n);
	const float refAlongEye = reflectionRay.dot(rayDirInv);

	if(refAlongEye > 0)
	{
		const float e = 16;
		return (pow(refAlongEye, e) * 255.0f * 0.8f);
	}
	else
		return 0;
}
int Light::getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	Vector start = getStart(point);
	float distance = start.to(point).len();

	float fallOff = pow(2.71828f, -(distance/500));

	return std::min(((255.0 * lightRayDir.inv().dot(normal.normal())) * fallOff), 255.0);
}
bool Light::inShadow(const Vector& point, const World& world) const
{
	Ray r(getStart(point), getDirection(point));
	r.onlyIntersection = true;
	world.getFirstHit(r);

	Vector dir = getStart(point).to(point);

	auto realTime = r.time;
	auto expectedTime = dir.len();
	return (realTime < expectedTime - 0.01);
}

