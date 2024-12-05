#ifndef VEC3D_HPP
#define VEC3D_HPP

#include <iostream>
#include "Mat4x4.hpp"

class Vec3d {
public:
	float x, y, z, w;
	Vec3d();

	Vec3d(float, float, float, float);

	void print(); /// for debugging

	float length() const;
	float dotProd(const Vec3d &, const Vec3d &);
	Vec3d crossProd(const Vec3d &, const Vec3d &);
	Vec3d& normalise();

	Vec3d& operator = (const Vec3d &);
	Vec3d& operator += (const Vec3d &);
	Vec3d& operator -= (const Vec3d &);
	Vec3d& operator *= (float);
	Vec3d& operator /= (float);

	Vec3d& operator *= (const Mat4x4&);
};

#endif

