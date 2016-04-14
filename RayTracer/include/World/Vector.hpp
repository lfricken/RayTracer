#pragma once

class Matrix;

namespace leon
{
	template<typename T>
	inline T sq(T x)
	{
		return x*x;
	}

	template<typename T>
	inline T min3(T x1, T x2, T x3)
	{
		return std::min(std::min(x1, x2), x3);
	}

	template<typename T>
	inline T max3(T x1, T x2, T x3)
	{
		return std::max(std::max(x1, x2), x3);
	}

	class Vector
	{
	public:
		Vector();
		Vector(float x , float y = 0, float z = 0, float w = 1);
		virtual ~Vector();
	
		float x;
		float y;
		float z;
		float w;

		bool init;

		Vector inv() const;
		float area(const Vector& b, const Vector& c) const;
		float dot(const Vector& other) const;//dot product
		Vector cross(const Vector& other) const;//cross product
		Vector reflect(const Vector& other) const;//reflect this across other
		float dist(const Vector& other) const;//distance
		float len() const;//length
		Vector normal() const;//return a vector that is normalized
		void normalize();//normalize this vector

		Vector to(const Vector& other) const;

		Vector operator-(const Vector& other) const;
		Vector operator+(const Vector& other) const;
		Vector operator*(float c) const;
		Vector operator/(float c) const;

		bool operator!=(const Vector& other) const;

	};


	/** 3x3 Matrix**/
	template<typename T>
	struct Mat3
	{
		Mat3()//sets up to be Identity Matrix by default
		{
			x1 = 1;
			x2 = 0;
			x3 = 0;
			y1 = 0;
			y2 = 1;
			y3 = 0;
			z1 = 0;
			z2 = 0;
			z3 = 1;
		}
		Mat3<T> operator+(const Mat3<T>& o) const//overloaded for addition by a Mat3
		{
			Mat3<T> result;
			result.x1 = x1 + o.x1;
			result.x2 = x2 + o.x2;
			result.x3 = x3 + o.x3;

			result.y1 = y1 + o.y1;
			result.y2 = y2 + o.y2;
			result.y3 = y3 + o.y3;

			result.z1 = z1 + o.z1;
			result.z2 = z2 + o.z2;
			result.z3 = z3 + o.z3;
			return result;
		}
		Mat3<T> operator*(float c) const//overloaded for multiplication by a constant
		{
			Mat3<T> result;
			result.x1 = x1*c;
			result.x2 = x2*c;
			result.x3 = x3*c;

			result.y1 = y1*c;
			result.y2 = y2*c;
			result.y3 = y3*c;

			result.z1 = z1*c;
			result.z2 = z2*c;
			result.z3 = z3*c;
			return result;
		}
		Vector operator*(const Vector& coord) const//overloaded for multiplication by a Vec3
		{
			Vector result;//maybe this could be optimized by using the constructor of Vec3
			result.x = x1*coord.x + x2*coord.y + x3*coord.z;
			result.y = y1*coord.x + y2*coord.y + y3*coord.z;
			result.z = z1*coord.x + z2*coord.y + z3*coord.z;
			return result;
		}
		Mat3<T> operator*(const Mat3<T>& mat) const
		{
			Mat3<T> result;
			result.x1 = x1*mat.x1 + x2*mat.y1 + x3*mat.z1;
			result.y1 = y1*mat.x1 + y2*mat.y1 + y3*mat.z1;
			result.z1 = z1*mat.x1 + z2*mat.y1 + z3*mat.z1;

			result.x2 = x1*mat.x2 + x2*mat.y2 + x3*mat.z2;
			result.y2 = y1*mat.x2 + y2*mat.y2 + y3*mat.z2;
			result.z2 = z1*mat.x2 + z2*mat.y2 + z3*mat.z2;

			result.x3 = x1*mat.x3 + x2*mat.y3 + x3*mat.z3;
			result.y3 = y1*mat.x3 + y2*mat.y3 + y3*mat.z3;
			result.z3 = z1*mat.x3 + z2*mat.y3 + z3*mat.z3;
			return result;
		}
		void setSkewSymCrossProd(const Vector& vec)//sets this matrix to be the skew-symetric cross-product of vec
		{
			x1 = 0;
			x2 = -vec.z;
			x3 = vec.y;

			y1 = vec.z;
			y2 = 0;
			y3 = -vec.x;

			z1 = -vec.y;
			z2 = vec.x;
			z3 = 0;
		}
		void setRotMat(Vector axis, float rads)//set this matrix to be the rotation matrix
		{
			axis.normalize();

			x1 = cos(rads) + sq(axis.x)*(1 - cos(rads));
			x2 = axis.x*axis.y*(1 - cos(rads)) - axis.z*sin(rads);
			x3 = axis.x*axis.z*(1 - cos(rads)) + axis.y*sin(rads);

			y1 = axis.y*axis.x*(1 - cos(rads)) + axis.z*sin(rads);
			y2 = cos(rads) + sq(axis.y)*(1 - cos(rads));
			y3 = axis.y*axis.z*(1 - cos(rads)) - axis.x*sin(rads);

			z1 = axis.z*axis.x*(1 - cos(rads)) - axis.y*sin(rads);
			z2 = axis.z*axis.y*(1 - cos(rads)) + axis.x*sin(rads);
			z3 = cos(rads) + sq(axis.z)*(1 - cos(rads));

		}
		void transpose()//set this matrix to be it's transpose
		{
			Mat3<T> copy = *this;

			x3 = copy.z1;
			x2 = copy.y1;
			y3 = copy.z2;

			y1 = copy.x2;
			z1 = copy.x3;
			z2 = copy.y3;
		}


		T x1, x2, x3;
		T y1, y2, y3;
		T z1, z2, z3;
	};
	typedef Mat3<float> Mat3d;
	typedef Mat3<float> Mat3f;
	typedef Mat3<int> Mat3i;



}



