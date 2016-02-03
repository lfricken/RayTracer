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

		virtual Vector getNormal(const Vector& point) const;

		Vector a;
		Vector b;
		Vector c;
		Plane plane;

	protected:
		virtual Vector intersectsHook(Ray& rRay, const World& world) const;
	};
}
