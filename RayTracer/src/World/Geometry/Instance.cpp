#include "Instance.hpp"

namespace leon
{
	Instance::Instance(const Geometry* pOriginal)
	{
		m_pParent = pOriginal;
	}
	Instance::~Instance()
	{

	}
	Vector Instance::getNormal(const Vector& point) const
	{
		auto trans = back*point;
		return m_pParent->getNormal(trans);
	}
	Vector Instance::intersectsHook(Ray& ray, const World& world) const
	{
		Ray trans = ray;
		trans.pos = back*ray.pos;//DOES NOT ACCOUNT FOR ANYTHING BUT TRANSLATION
		
		Vector ret = m_pParent->intersectsHook(trans, world);
		
		trans.pos = ray.pos;
		ray = trans;
		return ret;
	}
	void Instance::translate(const Vector& trans)
	{
		Matrix inv_translation_matrix;				// temporary inverse translation matrix	

		inv_translation_matrix.m[0][3] = -trans.x;
		inv_translation_matrix.m[1][3] = -trans.y;
		inv_translation_matrix.m[2][3] = -trans.z;

		back = back * inv_translation_matrix;

		Matrix translation_matrix;					// temporary translation matrix	

		translation_matrix.m[0][3] = trans.x;
		translation_matrix.m[1][3] = trans.y;
		translation_matrix.m[2][3] = trans.z;

		forward = translation_matrix * forward;
	}
	void Instance::transform(const Matrix& trans)
	{

	}
	void Instance::scale(const Vector& s)
	{

	}
	void Instance::shear(const Matrix& m)
	{

	}
	void Instance::rotate_x(const float radCCW)
	{

	}
	void Instance::rotate_y(const float radCCW)
	{

	}
	void Instance::rotate_z(const float radCCW)
	{

	}
	void Instance::calcBoundBox() const
	{
		m_box = BoundingBox();
	}
}

