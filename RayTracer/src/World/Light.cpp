#include "Light.hpp"

using namespace leon;

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
	return getBrightnessHook(point, normal, world);
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
