#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Plane : public Geometry
	{
	public:
		Plane(Vector pointi, Vector normali);
		virtual ~Plane();

		virtual Vector intersects(Ray& rRay) const;

		Vector point;
		Vector normal;

	};
}

