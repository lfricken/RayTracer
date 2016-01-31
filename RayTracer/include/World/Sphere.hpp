#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Sphere : public Geometry
	{
	public:
		Sphere(Vector position, double radiusi);
		virtual ~Sphere();

		virtual Vector intersects(Ray& rRay) const;

		Vector pos;
		double radius;

	};
}