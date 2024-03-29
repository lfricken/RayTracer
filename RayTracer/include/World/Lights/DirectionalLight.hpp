#pragma once

#include "Vector.hpp"
#include "Light.hpp"

namespace leon
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const sf::Color& colori, const Vector& directioni);
		~DirectionalLight();

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

	protected:
		virtual Vector getDirection(const Vector& point) const;
		virtual Vector getStart(const Vector& point) const;
	private:
		Vector direction;
	};
}
