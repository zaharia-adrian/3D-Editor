#ifndef MAT4X4_HPP
#define MAT4X4_HPP

#include <iostream>

class Vec3d;

class Mat4x4{
public:
	float m[4][4];

	Mat4x4();
	Mat4x4(std::initializer_list<float>);

	static Mat4x4 identity();

	void print() const; /// for debugging
	
	static Mat4x4 projection(float, float, float = acos(-1)*0.33f, float =0.1f, float =100.0f);
	static Mat4x4 translation(float, float, float);
	static Mat4x4 rotationX(float);
	static Mat4x4 rotationY(float);
	static Mat4x4 rotationZ(float);

	Mat4x4 operator = (const Mat4x4 &);
	Mat4x4& operator *= (const Mat4x4 &);
	Mat4x4 operator * (const Mat4x4 &);
	
};

#endif