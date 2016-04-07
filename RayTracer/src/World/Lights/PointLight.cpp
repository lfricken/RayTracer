#include "PointLight.hpp"
#include "Ray.hpp"
#include "World.hpp"

using namespace leon;

PointLight::PointLight(const sf::Color& color, const Vector& position) : Light(color)
{
	pos = position;
}
PointLight::~PointLight()
{

}
void PointLight::translate(const Vector& dist)
{
	pos = pos + dist;
}
void PointLight::transform(const Matrix& rot)
{
	pos = rot*pos;
}
Vector PointLight::getDirection(const Vector& point) const
{
	return pos.to(point).normal();
}
Vector PointLight::getStart(const Vector& point) const
{
	return pos;
}

