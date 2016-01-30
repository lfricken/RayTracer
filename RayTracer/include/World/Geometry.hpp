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

		virtual bool intersects(Ray& rRay) const = 0;

	};
}
