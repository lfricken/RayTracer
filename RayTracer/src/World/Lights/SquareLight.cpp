#include "SquareLight.hpp"
#include "Rectangle.hpp"

namespace leon
{
	SquareLight::SquareLight(const sf::Color& color, const Rectangle* rectangle) : Light(color)
	{
		m_shape.reset(rectangle);
	}
	SquareLight::~SquareLight()
	{

	}
	sf::Color SquareLight::getBrightness(const Vector& point, const Vector& normal, const World& world, const Material& material) const
	{
		Vector pos = m_shape->getPos();
		Vector axisA = m_shape->getAxisA();
		Vector axisB = m_shape->getAxisB();
		int r = 0, g = 0, b = 0;

		for(int a = 0; a <= m_rootSamples; ++a)
		{
			float fracA = static_cast<float>(a) / static_cast<float>(m_rootSamples);//calculate fractions
			for(int b = 0; b <= m_rootSamples; ++b)
			{
				float fracB = static_cast<float>(b) / static_cast<float>(m_rootSamples);//calculate fractions

				tempOrigin = pos + (axisA*fracA) + (axisB*fracB);

				sf::Color singleHit = Light::getBrightness(point, normal, world, material);

				r += singleHit.r;
				g += singleHit.g;
				b += singleHit.b;
			}
		}

		int totalSamples = m_rootSamples*m_rootSamples;
		return sf::Color(r / totalSamples, g / totalSamples, b / totalSamples);
	}
	Vector SquareLight::getDirection(const Vector& point) const
	{
		return tempOrigin.to(point);
	}
	Vector SquareLight::getStart(const Vector& point) const
	{
		return tempOrigin.normal();
	}
	void SquareLight::setSamples(int rootSamples)
	{
		m_rootSamples = rootSamples;
	}
}

