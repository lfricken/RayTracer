#pragma once

#include "Light.hpp"



namespace leon
{
	class Geometry;
	class Rectangle;

	class SquareLight : public Light
	{
	public:
		SquareLight(const sf::Color& color, const Rectangle* rectangle);
		virtual ~SquareLight();

		virtual sf::Color getBrightness(const Vector& point, const Vector& normal, const World& world, const Material& material) const;

		void setSamples(int rootSamples);
	protected:
		virtual Vector getDirection(const Vector& point) const;
		virtual Vector getStart(const Vector& point) const;

		sptr<const Rectangle> m_shape;
		int m_rootSamples;

		mutable Vector tempOrigin;
	};
}
