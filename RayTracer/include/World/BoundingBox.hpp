#pragma once

#include "Vector.hpp"
#include "stdafx.hpp"
#include "Ray.hpp"

namespace leon
{

	struct BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(const Vector& center, int size);

		Vector min;
		Vector max;

		vector<Vector> getCorners() const;
		int getHalfx() const;//half x distance
		Vector getCenter() const;//center of cube

		bool intersects(const BoundingBox& other) const;
		bool intersects(const Ray& ray) const;
		bool contains(const Vector& point) const;//Does this boundingbox surround that point?
	};
}
