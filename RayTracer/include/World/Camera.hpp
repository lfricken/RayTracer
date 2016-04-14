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

		void move(const Vector& dir, World& world);
		void yaw(float radCCW, World& world);
		void pitch(float radCCW, World& world);
		void roll(float radCCW, World& world);

		const Vector& getPosition() const;
		const Vector& getDirection() const;
		const Vector& getUp() const;

		float eyedist;
	protected:
		void transformWorld(Matrix rotMatrix, World& world) const;

		Vector position;
		Vector direction;
		Vector up;
		

	};
}
