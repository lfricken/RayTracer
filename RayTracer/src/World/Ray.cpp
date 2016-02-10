#include "Ray.hpp"

using namespace leon;

Ray::Ray(Vector position, Vector direction)
{
	pos = position;
	dir = direction.normal();
	lastColor = sf::Color(128, 128, 128, 255);
	time = -1;
}
Ray::~Ray()
{

}
void Ray::cast(const World& rWorld)
{

}
Vector Ray::getFuture(double t) const//get a point in the future of the ray
{
	return pos + (dir*t);
}