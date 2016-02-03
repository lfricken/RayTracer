#pragma once

#include "Vector.hpp"
#include "stdafx.hpp"

namespace leon
{
	class World;
	class Ray;
	class Geometry
	{
	public:
		Geometry();
		virtual ~Geometry();

		Vector intersects(Ray& ray, const World& world) const;

		sf::Color color;

		virtual Vector getNormal(const Vector& point) const = 0;

	protected:
		virtual Vector intersectsHook(Ray& ray, const World& world) const = 0;
	};
}
