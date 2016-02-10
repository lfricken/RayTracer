#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"

namespace leon
{
	class World;

	class Ray
	{
	public:
		Ray(Vector pos, Vector dir);
		virtual ~Ray();

		void cast(const World& rWorld);
		Vector getFuture(double t) const;//get a point in the future of the ray

		sf::Color lastColor;//last color we collided with
		double time;//time of our hit
		Vector pos;//start position
		Vector dir;//direction
	};
}
