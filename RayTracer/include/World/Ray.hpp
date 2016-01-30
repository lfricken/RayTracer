#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"

namespace leon
{
	class World;

	class Ray
	{
	public:
		Ray();
		virtual ~Ray();

		void cast(const World& rWorld);

		Vector pos;//start position
		Vector dir;//direction
	};
}
