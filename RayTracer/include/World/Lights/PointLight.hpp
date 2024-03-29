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

	protected:
		virtual Vector getDirection(const Vector& point) const;
		virtual Vector getStart(const Vector& point) const;

		Vector pos;
	};
}

