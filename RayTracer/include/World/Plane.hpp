#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Plane : public Geometry
	{
	public:
		Plane();
		virtual ~Plane();

		virtual Vector intersects(Ray& rRay) const;

		Vector normal;
		Vector point;
	};
}

