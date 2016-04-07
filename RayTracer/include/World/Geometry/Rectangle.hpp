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

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

		const Vector& getAxisA() const;
		const Vector& getAxisB() const;
		const Vector& getPos() const;


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
