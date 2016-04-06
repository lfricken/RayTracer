#pragma once

#include "Geometry.hpp"
#include "Triangle.hpp"

namespace leon
{
	class Rectangle : public Geometry
	{
	public:
		///Defined CCW
		Rectangle(Vector a, Vector b, Vector c, Vector d);
		~Rectangle();

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);


		virtual Vector getNormal(const Vector& point) const;
	protected:
		virtual void calcBoundBox() const;
		virtual Vector intersectsHook(Ray& ray, const World& world) const;
	private:
		Triangle first;
		Triangle second;
	};
}
