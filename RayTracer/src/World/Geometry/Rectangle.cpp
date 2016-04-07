#include "Rectangle.hpp"

using namespace leon;

Rectangle::Rectangle(Vector pos, Vector axisA, Vector axisB)
{
	first.reset(new Triangle(pos, pos + axisA, pos + axisB));
	second.reset(new Triangle(pos + axisA, pos + axisA + axisB, pos + axisB));

	m_pos = pos;
	m_axisA = axisA;
	m_axisB = axisB;
}
Rectangle::~Rectangle()
{

}
const Vector& Rectangle::getAxisA() const
{
	return m_axisA;
}
const Vector& Rectangle::getAxisB() const
{
	return m_axisB;
}
const Vector& Rectangle::getPos() const
{
	return m_pos;
}
Vector Rectangle::getNormal(const Vector& point) const
{
	return first->getNormal(point);
}
void Rectangle::calcBoundBox() const
{
	m_box = first->getBoundBox() + second->getBoundBox();
}
Vector Rectangle::intersectsHook(Ray& ray, const World& world) const
{
	Vector intersected;

	intersected = first->intersects(ray, world);
	if(intersected != Vector(0, 0, 0))
		return intersected;
	else
		return second->intersects(ray, world);
}
void Rectangle::translate(const Vector& dist)
{
	first->translate(dist);
	second->translate(dist);
}
void Rectangle::transform(const Matrix& rot)
{
	first->transform(rot);
	second->transform(rot);
}

