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
bool PointLight::inShadow(const Vector& origin, const Vector& direction, const Vector& point, const World& world) const
{
	Ray r(origin, direction);
	r.onlyIntersection = true;
	world.getFirstHit(r);

	Vector dir = pos.to(point);

	return (r.time < dir.len() - 0.01);
}

