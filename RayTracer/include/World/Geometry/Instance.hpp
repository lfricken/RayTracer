#pragma once

#include "Geometry.hpp"
#include "Matrix.hpp"

namespace leon
{
	class Instance : public Geometry
	{
	public:
		Instance(const Geometry* pOriginal);
		virtual ~Instance();

		virtual Vector getNormal(const Vector& point) const;

		void translate(const Vector& trans);
		void transform(const Matrix& trans);
		void scale(const Vector& s);
		void shear(const Matrix& m);
		void rotate_x(const float radCCW);
		void rotate_y(const float radCCW);
		void rotate_z(const float radCCW);


		Matrix forward;
		Matrix back;

		const Geometry* m_pParent;
	protected:

		virtual void calcBoundBox() const;

		virtual Vector intersectsHook(Ray& ray, const World& world) const;
	};
}
