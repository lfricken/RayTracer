#include "SquareLight.hpp"
#include "Rectangle.hpp"

namespace leon
{
	SquareLight::SquareLight(const sf::Color& color, Rectangle* rectangle) : Light(color)
	{
		m_shape.reset(rectangle);
		m_rootSamples = 7;
	}
	SquareLight::~SquareLight()
	{

	}
	sf::Color SquareLight::getBrightness(const Vector& point, const Vector& normal, const World& world, const Material& material) const
	{
		//Vector pos = m_shape->getPos();
		//Vector axisA = m_shape->getAxisA();
		//Vector axisB = m_shape->getAxisB();

		//int r = 0, g = 0, b = 0;

		//for(int j = 0; j < m_rootSamples; ++j)
		//{
		//	float fracB = static_cast<float>(j) / static_cast<float>(m_rootSamples);//calculate fractions

		//	tempOrigin = pos + (axisA * 0) + (axisB*fracB);

		//	sf::Color singleHit = Light::getBrightness(point, normal, world, material);

		//	r += singleHit.r;
		//	g += singleHit.g;
		//	b += singleHit.b;
		//}

		//return sf::Color(r / m_rootSamples, g / m_rootSamples, b / m_rootSamples);

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

				sf::Color singleHit = Light::getBrightness(point, normal, world, material);

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
		m_shape->translate(dist);
	}
	void SquareLight::transform(const Matrix& rot)
	{
		m_shape->transform(rot);
	}

}

