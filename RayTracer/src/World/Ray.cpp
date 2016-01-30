#include "Ray.hpp"

using namespace leon;

Ray::Ray()
{

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