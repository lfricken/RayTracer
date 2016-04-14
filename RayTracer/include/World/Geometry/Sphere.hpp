#pragma once

#include "Geometry.hpp"

namespace leon
{
	class Sphere : public Geometry
	{
	public:
		Sphere(Vector position, float radiusi);
		virtual ~Sphere();

		virtual Vector getNormal(const Vector& point) const;

		virtual void translate(const Vector& dist);
		virtual void transform(const Matrix& rot);

	protected:
		virtual void calcBoundBox() const;
		virtual bool intersectsHook(Ray& rRay, const World& world) const;

		Vector pos;
		float radius;

	};
}