#include "Light.hpp"

using namespace leon;

Light::Light(const sf::Color& colori)
{
	color = colori;
}
Light::~Light()
{

}
sf::Color Light::getBrightness(const Vector& point, const Vector& normal, const World& world) const
{
	return getBrightnessHook(point, normal, world);
}
const sf::Color& Light::getColor() const
{
	return color;
}
void Light::setColor(const sf::Color& newColor)
{
	color = newColor;
}
