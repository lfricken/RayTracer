#include "SquareLight.hpp"
#include "Rectangle.hpp"
#include "Ray.hpp"

namespace leon
{
	SquareLight::SquareLight(const sf::Color& color, Rectangle* rectangle, int samples) : Light(color)
	{
		m_shape.reset(rectangle);
		rectangle->light = true;
		rectangle->material.color = color;
		m_rootSamples = samples;
	}
	SquareLight::~SquareLight()
	{

	}
	sf::Color SquareLight::getBrightness(const Ray& ray, const Vector& point, const Vector& normal, const World& world, const Material& material) const
	{
		Vector pos = m_shape->getPos();
		Vector axisA = m_shape->getAxisA();
		Vector axisB = m_shape->getAxisB();
		int r = 0, g = 0, b = 0;

		for(int i = 0; i <= m_rootSamples; ++i)
		{
			float fracA = static_cast<float>(i) / static_cast<float>(m_rootSamples);//calculate fractions
			for(int j = 0; j <= m_rootSamples; ++j)
			{
				float fracB = static_cast<float>(j) / static_cast<float>(m_rootSamples);//calculate fractions

				tempOrigin = pos + (axisA*fracA) + (axisB*fracB);

				sf::Color singleHit = Light::getBrightness(ray, point, normal, world, material);

				r += singleHit.r;
				g += singleHit.g;
				b += singleHit.b;
			}
		}

		int totalSamples = (m_rootSamples+1)*(m_rootSamples+1);
		return sf::Color(r / totalSamples, g / totalSamples, b / totalSamples);
	}
	Vector SquareLight::getDirection(const Vector& point) const
	{
		return tempOrigin.to(point).normal();
	}
	Vector SquareLight::getStart(const Vector& point) const
	{
		return tempOrigin;
	}
	void SquareLight::setSamples(int rootSamples)
	{
		m_rootSamples = rootSamples;
	}
	void SquareLight::translate(const Vector& dist)
	{
		//m_shape->translate(dist);
	}
	void SquareLight::transform(const Matrix& rot)
	{
		//m_shape->transform(rot);
	}

}

