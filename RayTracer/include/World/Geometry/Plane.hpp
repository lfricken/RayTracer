#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Plane : public Geometry
	{
	public:
		Plane(Vector pointi, Vector normali);
		virtual ~Plane();

		virtual Vector getNormal(const Vector& point) const;

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

		Vector point;
		Vector normal;

	protected:
		virtual void calcBoundBox() const;
		virtual bool intersectsHook(Ray& rRay, const World& world) const;
	};
}

