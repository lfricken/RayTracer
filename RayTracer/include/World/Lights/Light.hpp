#pragma once

#include "Scenic.hpp"
#include "stdafx.hpp"

struct Material;

namespace leon
{
	class Vector;
	class World;
	class Light : public Scenic
	{
	public:
		Light(const sf::Color& colori);
		~Light();

		sf::Color getBrightness(const Vector& point, const Vector& normal, const World& world, const Material& material) const;

	protected:
		int getSpecular(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;
		int getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;
		
		virtual bool inShadow(const Vector& origin, const Vector& direction, const Vector& point, const World& world) const = 0;
		virtual Vector getDirection(const Vector& point) const = 0;
		virtual Vector getStart(const Vector& point) const = 0;

	private:
		sf::Color color;
	};
}
