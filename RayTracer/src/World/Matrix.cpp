// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class Matrix

#include "Matrix.hpp"
#include "Vector.hpp"
#include "stdafx.hpp"


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



Matrix::Matrix()
{
	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
		{
			if(x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}
Matrix::Matrix(const Matrix& mat)
{
	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
			m[x][y] = mat.m[x][y];
}
Matrix::~Matrix()
{

}
Matrix& Matrix::operator= (const Matrix& rhs)
{
	if(this == &rhs)
		return (*this);

	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
			m[x][y] = rhs.m[x][y];

	return (*this);
}
leon::Vector Matrix::operator*(const leon::Vector& v) const
{
	const Matrix& mat = *this;
	return (leon::Vector(
		mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z + mat.m[0][3] * v.w,
		mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z + mat.m[1][3] * v.w,
		mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z + mat.m[2][3] * v.w,
		mat.m[3][0] * v.x + mat.m[3][1] * v.y + mat.m[3][2] * v.z + mat.m[3][3] * v.w
		));
}
Matrix Matrix::operator* (const Matrix& mat) const
{
	Matrix 	product;

	for(int y = 0; y < 4; y++)
		for(int x = 0; x < 4; x++)
		{
			float sum = 0.0;

			for(int j = 0; j < 4; j++)
				sum += m[x][j] * mat.m[j][y];

			product.m[x][y] = sum;
		}

	return (product);
}
Matrix Matrix::operator/ (const float d)
{
	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
			m[x][y] = m[x][y] / d;

	return (*this);
}
void Matrix::set_identity()
{
	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
		{
			if(x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}
void Matrix::setRotMat(leon::Vector axis, float rads)//set this matrix to be the rotation matrix
{
	axis.normalize();

	m[0][0] = cos(rads) + sq(axis.x)*(1 - cos(rads));
	m[0][1] = axis.x*axis.y*(1 - cos(rads)) - axis.z*sin(rads);
	m[0][2] = axis.x*axis.z*(1 - cos(rads)) + axis.y*sin(rads);
	m[0][3] = 0;

	m[1][0] = axis.y*axis.x*(1 - cos(rads)) + axis.z*sin(rads);
	m[1][1] = cos(rads) + sq(axis.y)*(1 - cos(rads));
	m[1][2] = axis.y*axis.z*(1 - cos(rads)) - axis.x*sin(rads);
	m[1][3] = 0;

	m[2][0] = axis.z*axis.x*(1 - cos(rads)) - axis.y*sin(rads);
	m[2][1] = axis.z*axis.y*(1 - cos(rads)) + axis.x*sin(rads);
	m[2][2] = cos(rads) + sq(axis.z)*(1 - cos(rads));
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}
void Matrix::transpose()//set this matrix to be it's transpose
{
	Matrix copy = *this;

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			m[i][j] = copy.m[j][i];
}
float Matrix::det() const
{
	float det = 0;

	det += (m[0][0] * m[1][1] * m[2][2] * m[3][3]) + (m[0][0] * m[1][2] * m[2][3] * m[3][1]) + (m[0][0] * m[1][3] * m[2][1] * m[3][2]);
	det += (m[0][1] * m[1][0] * m[2][3] * m[3][2]) + (m[0][1] * m[1][2] * m[2][0] * m[3][3]) + (m[0][1] * m[1][3] * m[2][2] * m[3][0]);
	det += (m[0][2] * m[1][0] * m[2][1] * m[3][3]) + (m[0][2] * m[1][1] * m[2][3] * m[3][0]) + (m[0][2] * m[1][3] * m[2][0] * m[3][1]);
	det += (m[0][3] * m[1][0] * m[2][2] * m[3][1]) + (m[0][3] * m[1][1] * m[2][0] * m[3][2]) + (m[0][3] * m[1][2] * m[2][1] * m[3][0]);

	det -= (m[0][0] * m[1][1] * m[2][3] * m[3][2]) + (m[0][0] * m[1][2] * m[2][1] * m[3][3]) + (m[0][0] * m[1][3] * m[2][2] * m[3][1]);
	det -= (m[0][1] * m[1][0] * m[2][2] * m[3][3]) + (m[0][1] * m[1][2] * m[2][3] * m[3][0]) + (m[0][1] * m[1][3] * m[2][0] * m[3][2]);
	det -= (m[0][2] * m[1][0] * m[2][3] * m[3][1]) + (m[0][2] * m[1][1] * m[2][0] * m[3][3]) + (m[0][2] * m[1][3] * m[2][1] * m[3][0]);
	det -= (m[0][3] * m[1][0] * m[2][1] * m[3][2]) + (m[0][3] * m[1][1] * m[2][2] * m[3][0]) + (m[0][3] * m[1][2] * m[2][0] * m[3][1]);

	return det;
}





