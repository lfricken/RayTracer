#pragma once

#include "Geometry.hpp"
#include "Plane.hpp"

namespace leon
{
	class Triangle : public Geometry
	{
	public:
		Triangle(Vector a, Vector b, Vector c);
		virtual ~Triangle();

		virtual Vector getNormal(const Vector& point) const;

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

		Vector a;
		Vector b;
		Vector c;
		sptr<Plane> plane;

	protected:
		virtual void calcBoundBox() const;
		virtual bool intersectsHook(Ray& rRay, const World& world) const;
	};
}
