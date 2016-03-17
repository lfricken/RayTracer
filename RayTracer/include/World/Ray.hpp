#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"

namespace leon
{
	class World;
	class Geometry;

	class Ray
	{
	public:
		Ray(Vector pos, Vector dir);
		virtual ~Ray();

		Vector getFuture(double t) const;//get a point in the future of the ray

		bool onlyIntersection;
		sf::Color lastColor;//last color we collided with
		double time;//time of our hit
		Vector pos;//start position
		Vector dir;//direction

		const Geometry* lastHit;
	};
}
