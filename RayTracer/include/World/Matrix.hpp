#pragma once
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

//----------------------------------------- class Matrix
namespace leon
{
	class Vector;

}

class Matrix
{

public:
	Matrix();
	Matrix(const Matrix& mat);
	~Matrix();

	Matrix& operator= (const Matrix& rhs);
	Matrix operator* (const Matrix& mat) const;
	leon::Vector operator*(const leon::Vector& rhs) const;
	Matrix operator/ (const float d);

	void set_identity();
	void setRotMat(leon::Vector axis, float rads);
	float det() const;
	void transpose();

	float m[4][4];//(row, column)
};




