#pragma once

#include "Geometry.hpp"
#include "Matrix.hpp"

namespace leon
{
	class Instance : public Geometry
	{
	public:
		Instance(Geometry* pOriginal);
		virtual ~Instance();



		virtual Vector getNormal(const Vector& point);
		Matrix translation;
		Matrix invTranslation;
		Geometry* m_pParent;
	protected:
		virtual Vector intersectsHook(Ray& ray, const World& world);
	};
}
