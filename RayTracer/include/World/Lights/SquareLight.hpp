#pragma once

#include "Light.hpp"



namespace leon
{
	class Geometry;
	class Rectangle;

	class SquareLight : public Light
	{
	public:
		SquareLight(const sf::Color& color, Rectangle* rectangle, int samples);
		virtual ~SquareLight();

		virtual sf::Color getBrightness(const Ray& ray, const Vector& point, const Vector& normal, const World& world, const Material& material) const;

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

		void setSamples(int rootSamples);
	protected:
		virtual Vector getDirection(const Vector& point) const;
		virtual Vector getStart(const Vector& point) const;

		sptr<Rectangle> m_shape;
		int m_rootSamples;

		mutable Vector tempOrigin;
	};
}
