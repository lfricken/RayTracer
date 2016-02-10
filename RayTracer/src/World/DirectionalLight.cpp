#include "DirectionalLight.hpp"

using namespace leon;

DirectionalLight::DirectionalLight(const sf::Color& colori, const Vector& directioni) : Light(colori)
{
	direction = directioni.normal();
}
DirectionalLight::~DirectionalLight()
{

}
/// <summary>
/// determines how bright we are illuminating something
/// </summary>
/// <param name="point">The point.</param>
/// <param name="normal">The normal.</param>
/// <param name="world">The world.</param>
/// <returns>brightness</returns>
sf::Color DirectionalLight::getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const
{
	double c = 255 * direction.inv().dot(normal.normal());
	if(c >= 0)
		return color*sf::Color(c, c, c);
	else
		return color*sf::Color(0, 0, 0);
}
/// <summary>
/// Translates the specified distance.
/// </summary>
/// <param name="dist">The dist.</param>
void DirectionalLight::translate(const Vector& dist)
{

}
/// <summary>
/// Transforms the specified rotation.
/// </summary>
/// <param name="rot">The rot.</param>
void DirectionalLight::transform(const Matrix& rot)
{
	direction = rot*direction;
}


