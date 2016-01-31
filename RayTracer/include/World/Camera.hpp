#pragma once

#include "Vector.hpp"

namespace leon
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		Vector position;
		Vector direction;
		double rotation;//NOT USED YET
	};
}
