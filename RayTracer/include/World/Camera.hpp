#pragma once

#include "Vector.hpp"

namespace leon
{
	class World;
	class Camera
	{
	public:
		Camera();
		~Camera();

		void move(const Vector& pos, World& world);
		void yaw(double radCCW, World& world);
		void pitch(double radCCW, World& world);
		void roll(double radCCW, World& world);

		const Vector& getPosition();
		const Vector& getDirection();
		const Vector& getUp();

		double eyedist;
	protected:
		Vector position;
		Vector direction;
		Vector up;
		

	};
}
