#pragma once

#include "Scenic.hpp"
#include "stdafx.hpp"

namespace leon
{
	class Vector;
	class World;
	class Light : public Scenic
	{
	public:
		Light(const sf::Color& colori);
		~Light();

		sf::Color getBrightness(const Vector& point, const Vector& normal, const World& world) const;

		const sf::Color& getColor() const;
		void setColor(const sf::Color& newColor);

	protected:
		double getSpecular(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;
		double getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;

		virtual sf::Color getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const = 0;

		sf::Color color;
	};
}
