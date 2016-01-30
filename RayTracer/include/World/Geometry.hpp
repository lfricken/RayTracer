#pragma once

#include "Vector.hpp"

namespace leon
{
	class Ray;
	class Geometry
	{
	public:
		Geometry();
		virtual ~Geometry();

		virtual Vector intersects(Ray& rRay) const = 0;

	};
}
