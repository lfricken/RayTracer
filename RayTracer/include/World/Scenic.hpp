#pragma once

#include "Vector.hpp"

namespace leon
{
	class Vector;
	class Scenic
	{
	public:
		Scenic();
		~Scenic();

		virtual void translate(const Vector& dist) = 0;
		virtual void transform(const Matrix& rot) = 0;
	};
}
