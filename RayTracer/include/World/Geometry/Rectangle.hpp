#pragma once

#include "Geometry.hpp"
#include "Triangle.hpp"

namespace leon
{
	class Rectangle : public Geometry
	{
	public:
		///Defined CCW
		Rectangle(Vector pos, Vector axisA, Vector axisB);
		~Rectangle();

		virtual sf::Color getColorPoint(const Ray& ray, const Vector& point, const World& world) const;

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

		const Vector& getAxisA() const;
		const Vector& getAxisB() const;
		const Vector& getPos() const;

		bool light;

		virtual Vector getNormal(const Vector& point) const;
	protected:
		virtual void calcBoundBox() const;
		virtual Vector intersectsHook(Ray& ray, const World& world) const;

		Vector m_pos;
		Vector m_axisA;
		Vector m_axisB;
	private:
		sptr<Triangle> first;
		sptr<Triangle> second;
	};
}
