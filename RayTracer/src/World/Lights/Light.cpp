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
sf::Color Light::getBrightness(const Vector& point, const Vector& normal, const World& world, const Material& material) const
{
	const Vector direction = this->getDirection(point);
	const Vector start = this->getStart(point);
	const sf::Color& ambient = world.ambientLight;

	if(!inShadow(start, direction, point, world))
	{
		const int diffValue = getDiffuse(point, normal, world, direction);
		const float diffFrac = material.diffuse*static_cast<float>(diffValue) / 255.f;
		const sf::Color diffuse = material.color * sf::Color(diffFrac * color.r, diffFrac * color.g, diffFrac * color.b);

		const int specValue = getSpecular(point, normal, world, getDirection(point));
		const float specFrac = material.specular*static_cast<float>(specValue) / 255.f;
		const sf::Color specular = sf::Color::White * sf::Color(specFrac * color.r, specFrac * color.g, specFrac * color.b);

		return sf::Color(std::min(255, diffuse.r + specular.r + ambient.r), std::min(255, diffuse.g + specular.g + ambient.g), std::min(255, diffuse.b + specular.b + ambient.b));
	}
	else
		return ambient;
}
int Light::getSpecular(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	const Vector toEye = point.to(world.camera.getPosition()).normal();

	const Vector p = point.normal();
	const Vector n = normal.normal();
	const Vector l = lightRayDir.normal();

	const double e = 16;

	const Vector specVector = (l - (n * (l.dot(n) * 2))).normal();

	return (pow(specVector.dot(toEye), e) * 255 * 0.8);
}
int Light::getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	return (255.0 * lightRayDir.inv().dot(normal.normal()));
}