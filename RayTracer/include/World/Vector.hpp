#pragma once

namespace leon
{
	class Vector
	{
	public:
		Vector();
		Vector(double x , double y = 0, double z = 0);
		virtual ~Vector();
	
		double x;
		double y;
		double z;

		bool init;

		double area(const Vector& b, const Vector& c) const;
		double dot(const Vector& other) const;//dot product
		double dist(const Vector& other) const;//distance
		double len() const;//length

		Vector to(const Vector& other) const;

		Vector operator-(const Vector& other) const;
		Vector operator+(const Vector& other) const;
		Vector operator*(double c) const;
		Vector operator/(double c) const;

	};
}
