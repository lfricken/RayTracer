#pragma once

#include "Light.hpp"
#include "Vector.hpp"


namespace leon
{
	class PointLight : public Light
	{
	public:
		PointLight(const sf::Color& color, const Vector& position);
		~PointLight();

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

		virtual Vector getDirection(const Vector& point) const;
		virtual Vector getStart(const Vector& point) const;

	protected:
		virtual bool inShadow(const Vector& origin, const Vector& direction, const Vector& point, const World& world) const;

		Vector pos;
	};
}

