#include "DirectionalLight.hpp"

using namespace leon;

DirectionalLight::DirectionalLight(const sf::Color& colori, const Vector& directioni) : Light(colori)
{
	direction = directioni.normal();
}
DirectionalLight::~DirectionalLight()
{

}
sf::Color DirectionalLight::getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const
{
	double c = 255 * direction.inv().dot(normal.normal());
	if(c >= 0)
		return color*sf::Color(c, c, c);
	else
		return color*sf::Color(0, 0, 0);
}
void DirectionalLight::translate(const Vector& dist)
{

}
void DirectionalLight::transform(const Matrix& rot)
{
	direction = rot*direction;
}


