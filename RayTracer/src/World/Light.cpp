#include "Light.hpp"
#include "World.hpp"

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
double Light::getSpecular(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	Vector toEye = point.to(world.camera.getPosition());

	return 0;
}
double Light::getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const
{
	return 255 * lightRayDir.inv().dot(normal.normal());
}

