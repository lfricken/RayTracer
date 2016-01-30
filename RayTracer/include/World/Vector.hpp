#pragma once

namespace leon
{
	class Vector
	{
	public:
		Vector(double x = 0, double y = 0, double z = 0);
		virtual ~Vector();
	
		double x;
		double y;
		double z;

		double dot(const Vector& other) const;

	};
}
