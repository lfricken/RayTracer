#include "BoundingBox.hpp"

using namespace leon;

BoundingBox::BoundingBox()
{

}
BoundingBox::BoundingBox(const Vector& center, int size)
{
	int halfSize = size / 2;

	min.x = center.x - halfSize;
	min.y = center.y - halfSize;
	min.z = center.z - halfSize;

	max.x = center.x + halfSize;
	max.y = center.y + halfSize;
	max.z = center.z + halfSize;
}
Vector BoundingBox::getCenter() const
{
	return Vector((min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2);
}
bool BoundingBox::contains(const Vector& point) const
{
	return (point.x >= min.x && point.x <= max.x) && (point.y >= min.y && point.y <= max.y) && (point.z >= min.z && point.z <= max.z);
}
int BoundingBox::getHalfx() const
{
	return (max.x - min.x) / 2;
}
vector<Vector> BoundingBox::getCorners() const
{
	vector<Vector> corners;

	corners.push_back(Vector(min.x, min.y, min.z));
	corners.push_back(Vector(max.x, min.y, min.z));

	corners.push_back(Vector(min.x, max.y, min.z));
	corners.push_back(Vector(max.x, max.y, min.z));

	corners.push_back(Vector(min.x, min.y, max.z));
	corners.push_back(Vector(max.x, min.y, max.z));

	corners.push_back(Vector(min.x, max.y, max.z));
	corners.push_back(Vector(max.x, max.y, max.z));
	
	return corners;
}
bool BoundingBox::intersects(const BoundingBox& other) const
{
	if(min.x > other.max.x)
		return false;
	if(min.y > other.max.y)
		return false;
	if(min.z > other.max.z)
		return false;


	if(other.min.x > max.x)
		return false;
	if(other.min.y > max.y)
		return false;
	if(other.min.z >max.z)
		return false;

	return true;
}
bool BoundingBox::intersects(const Ray& ray) const
{
	return false;//TOODO
}


