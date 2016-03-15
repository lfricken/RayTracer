#pragma once

#include "Vector.hpp"
#include "stdafx.hpp"

namespace leon
{

	struct BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(const Vector& center, int halfSize);

		Vector min;
		Vector max;

		vector<Vector> getCorners() const;
		int getHalfx() const;//half x distance
		Vector getCenter() const;//center of cube
		bool contains(const Vector& point) const;//Does this boundingbox surround that point?
	};
}
