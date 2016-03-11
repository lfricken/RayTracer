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

		virtual Vector getDirection(const Vector& point) const = 0;

		const sf::Color& getColor() const;
		void setColor(const sf::Color& newColor);

	protected:
		unsigned char getSpecular(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;
		unsigned char getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;

		bool inShadow(const Vector& origin, const Vector& direction, const Vector& target, const World& world) const;

		sf::Color getBrightnessHook(const Vector& point, const Vector& normal, const World& world) const;

		sf::Color color;
	};
}
