#pragma once

#include "Scenic.hpp"
#include "stdafx.hpp"

struct Material;


namespace leon
{
	class Ray;
	class Vector;
	class World;
	class Light : public Scenic
	{
	public:
		Light(const sf::Color& colori);
		~Light();

		virtual sf::Color getBrightness(const Ray& ray, const Vector& point, const Vector& normal, const World& world, const Material& material) const;

	protected:
		int getSpecular(const Ray& ray, const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;
		int getDiffuse(const Vector& point, const Vector& normal, const World& world, const Vector& lightRayDir) const;
		bool inShadow(const Vector& point, const World& world) const;

		virtual Vector getDirection(const Vector& point) const = 0;
		virtual Vector getStart(const Vector& point) const = 0;

	private:
		sf::Color color;
	};
}
