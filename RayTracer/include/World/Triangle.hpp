#pragma once

#include "Geometry.hpp"
#include "Plane.hpp"

namespace leon
{
	class Triangle : public Geometry
	{
	public:
		Triangle(Vector a, Vector b, Vector c);
		virtual ~Triangle();

		virtual Vector intersects(Ray& rRay) const;

		Vector a;
		Vector b;
		Vector c;
		Plane plane;
	};
}
