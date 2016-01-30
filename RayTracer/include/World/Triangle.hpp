#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Triangle : public Geometry
	{
	public:
		Triangle(Vector a, Vector b, Vector c);
		virtual ~Triangle();

		virtual Vector intersects(Ray& rRay) const;
		double myArea() const;

		Vector a;
		Vector b;
		Vector c;
		Vector normal;
	};
}
