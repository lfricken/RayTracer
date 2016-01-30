#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Triangle : public Geometry
	{
	public:
		Triangle();
		virtual ~Triangle();

		virtual bool intersects(Ray& rRay) const;

		Vector a;
		Vector b;
		Vector c;
		Vector normal;
	};
}
