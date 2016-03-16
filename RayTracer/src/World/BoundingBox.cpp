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
/// <summary>
/// Intersectses the specified ray.
/// </summary>
/// https://tavianator.com/fast-branchless-raybounding-box-intersections/
/// <returns></returns>
bool BoundingBox::intersects(const Ray& ray) const
{
	double tmin = -999999999, tmax = 999999999;

	if(ray.dir.x != 0.0)
	{
		double txmin = (min.x - ray.pos.x) / ray.dir.x;
		double txmax = (max.x - ray.pos.x) / ray.dir.x;

		tmin = std::min(txmin, txmax);
		tmax = std::max(txmin, txmax);
	}

	if(ray.dir.y != 0.0)
	{
		double tymin = (min.y - ray.pos.y) / ray.dir.y;
		double tymax = (max.y - ray.pos.y) / ray.dir.y;

		tmin = std::max(tmin, std::min(tymin, tymax));
		tmax = std::min(tmax, std::max(tymin, tymax));
	}

	if(ray.dir.z != 0.0)
	{
		double tzmin = (min.z - ray.pos.z) / ray.dir.z;
		double tzmax = (max.z - ray.pos.z) / ray.dir.z;

		tmin = std::max(tmin, std::min(tzmin, tzmax));
		tmax = std::min(tmax, std::max(tzmin, tzmax));
	}

	return tmax >= tmin;
}


