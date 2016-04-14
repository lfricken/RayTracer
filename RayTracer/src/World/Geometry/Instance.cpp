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
	bool Instance::intersectsHook(Ray& ray, const World& world) const
	{
		Ray trans = ray;
		trans.dir = back*trans.dir;
		trans.dir.normalize();
		trans.pos = back*ray.pos;
		
		bool intersected = m_pParent->intersectsHook(trans, world);
		
		trans.pos = ray.pos;
		trans.dir = ray.dir;
		ray = trans;
		return intersected;
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
		Matrix	inv_scaling_matrix;			// temporary inverse scaling matrix

		inv_scaling_matrix.m[0][0] = 1.0 / s.x;
		inv_scaling_matrix.m[1][1] = 1.0 / s.y;
		inv_scaling_matrix.m[2][2] = 1.0 / s.z;

		back = back * inv_scaling_matrix;

		Matrix	scaling_matrix;				// temporary scaling matrix

		scaling_matrix.m[0][0] = s.x;
		scaling_matrix.m[1][1] = s.y;
		scaling_matrix.m[2][2] = s.z;

		forward = scaling_matrix * forward;
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

