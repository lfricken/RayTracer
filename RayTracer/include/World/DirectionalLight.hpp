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

		Vector direction;

	protected:
		virtual sf::Color getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const;
	};
}
