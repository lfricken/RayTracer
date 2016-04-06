#include "Rectangle.hpp"

using namespace leon;

Rectangle::Rectangle(Vector a, Vector b, Vector c, Vector d) : first(a, b, c), second(c, d, a)
{

}
Rectangle::~Rectangle()
{

}
Vector Rectangle::getNormal(const Vector& point) const
{
	return first.getNormal(point);
}
void Rectangle::calcBoundBox() const
{
	m_box = first.getBoundBox() + second.getBoundBox();
}
Vector Rectangle::intersectsHook(Ray& ray, const World& world) const
{
	Vector intersected;

	intersected = first.intersects(ray, world);
	if(intersected != Vector(0, 0, 0))
		return intersected;
	else
		return second.intersects(ray, world);
}
void Rectangle::translate(const Vector& dist)
{
	first.translate(dist);
	second.translate(dist);
}
void Rectangle::transform(const Matrix& rot)
{
	first.transform(rot);
	second.transform(rot);
}

