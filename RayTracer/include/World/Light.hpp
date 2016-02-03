#pragma once

#include "stdafx.hpp"

namespace leon
{
	class Vector;
	class World;
	class Light
	{
	public:
		Light(const sf::Color& colori);
		~Light();

		sf::Color getBrightness(const Vector& point, const Vector& normal, const World& world) const;

		const sf::Color& getColor() const;
		void setColor(const sf::Color& newColor);

	protected:
		virtual sf::Color getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const = 0;

		sf::Color color;
	};
}
