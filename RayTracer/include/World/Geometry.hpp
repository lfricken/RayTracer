#pragma once

#include "Vector.hpp"
#include "stdafx.hpp"
#include "Scenic.hpp"
#include "BoundingBox.hpp"

namespace leon
{
	class World;
	class Ray;
	class Geometry : public Scenic
	{
	public:
		Geometry();
		virtual ~Geometry();

		Vector intersects(Ray& ray, const World& world) const;
		const BoundingBox& getBoundBox() const;

		sf::Color color;

		virtual Vector getNormal(const Vector& point) const = 0;

		//TODO MAKE CAMERA ROTATION set this to FALSE
		mutable bool m_boxCalculated;//has our bounding box been calculated already
	protected:
		mutable BoundingBox m_box;

		virtual void calcBoundBox() const = 0;
		virtual Vector intersectsHook(Ray& ray, const World& world) const = 0;
	};
}
