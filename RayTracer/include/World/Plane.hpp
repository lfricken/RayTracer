#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Plane : public Geometry
	{
	public:
		Plane(Vector pointi, Vector normali);
		virtual ~Plane();

		virtual Vector getNormal(const Vector& point) const;

		Vector point;
		Vector normal;

	protected:
		virtual Vector intersectsHook(Ray& rRay, const World& world) const;
	};
}

