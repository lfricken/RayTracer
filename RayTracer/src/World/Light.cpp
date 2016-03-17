#include "Light.hpp"
#include "World.hpp"
#include "Ray.hpp"

#include <algorithm>

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
sf::Color Light::getBrightness(const Vector& point, const Vector& normal, const World& world) const
{
	sf::Color c = getBrightnessHook(point, normal, world);
	const sf::Color& amb = world.ambientLight;
	return sf::Color(min(255, (amb.r + c.r)), min(255, (amb.g + c.g)), min(255, (amb.b + c.b)));
}
/// <summary>
/// Gets the color of light
/// </summary>
/// <returns>color of light</returns>
const sf::Color& Light::getColor() const
{
	return color;
}
/// <summary>
/// Sets the color.
/// </summary>
/// <param name="newColor">The new color.</param>
void Light::setColor(const sf::Color& newColor)
{
	color = newColor;
}
int Light::getSpecular(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	Vector toEye = point.to(world.camera.getPosition());

	Vector p = point.normal();
	Vector n = normal.normal();
	Vector l = lightRayDir.normal();
	toEye.normalize();

	double e = 16;

	Vector specVector = lightRayDir - (normal * (lightRayDir.dot(normal) * 2));

	return (pow(specVector.dot(toEye), e) * 255 * 0.8);
}
int Light::getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	return (255.0 * lightRayDir.inv().dot(normal.normal()));
}
/// <summary>
/// determines how bright we are illuminating something
/// </summary>
/// <param name="point">The point.</param>
/// <param name="normal">The normal.</param>
/// <param name="world">The world.</param>
/// <returns>brightness</returns>
sf::Color Light::getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const
{
	Vector direction = this->getDirection(point);

	Vector start = this->getStart(point);
		//start(point.x - direction.x * 2000, point.y - direction.y * 2000, point.z - direction.z * 2000);

	if(!inShadow(start, direction, point, world))
	{
		//Diffuse
		int d = getDiffuse(point, normal, world, direction);
		int s = 0;// getSpecular(point, normal, world, direction);

		if(d > 0)
			return color*sf::Color(min(s + d, 255), min(s + d, 255), min(s + d, 255));//TODO THIS SHOULD REFERENCE COLOR OF THIS LIGHT
		else
			return sf::Color(0, 0, 0);
	}
	else
		return sf::Color(0, 0, 0);
}

