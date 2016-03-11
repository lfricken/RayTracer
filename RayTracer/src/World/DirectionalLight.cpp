#include "DirectionalLight.hpp"
#include "World.hpp"

using namespace leon;
using namespace std;

DirectionalLight::DirectionalLight(const sf::Color& colori, const Vector& directioni) : Light(colori)
{
	direction = directioni.normal();
}
DirectionalLight::~DirectionalLight()
{

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
Vector DirectionalLight::getDirection(const Vector& point) const
{
	return direction;
}

