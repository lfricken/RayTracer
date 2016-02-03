#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Sphere : public Geometry
	{
	public:
		Sphere(Vector position, double radiusi);
		virtual ~Sphere();

		virtual Vector getNormal(const Vector& point) const;

	protected:
		virtual Vector intersectsHook(Ray& rRay, const World& world) const;

		Vector pos;
		double radius;

	};
}