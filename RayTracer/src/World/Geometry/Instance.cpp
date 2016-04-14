#include "Instance.hpp"

namespace leon
{
	Instance::Instance(Geometry* pOriginal)
	{
		m_pParent = pOriginal;
	}
	Instance::~Instance()
	{

	}
	Vector Instance::getNormal(const Vector& point)
	{
		Vector translatedPoint = invTranslation*point;
		Vector normal = m_pParent->getNormal(translatedPoint);
		return translation*normal;
	}
	Vector Instance::intersectsHook(Ray& ray, const World& world)
	{
		return Vector();
	}
}

