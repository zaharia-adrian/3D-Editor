#ifndef VEC3D_HPP
#define VEC3D_HPP

#include <iostream>
#include <string>
#include "Mat4x4.hpp"
#include "Quaternion.hpp"

class Vec3d {
public:
	float x, y, z, w;
	Vec3d();

	Vec3d(float, float, float, float = 1);
	

	void print(std::string = "") const; /// for debugging

	float getLength() const;
	float dotProd(const Vec3d &) const;
	Vec3d crossProd(const Vec3d &) const;
	Vec3d& normalize();
	Vec3d& rotate(const Vec3d&, float theta);

	Vec3d& operator = (const Vec3d &);
	Vec3d& operator += (const Vec3d &);
	Vec3d& operator -= (const Vec3d &);
	Vec3d& operator *= (float);
	Vec3d& operator /= (float);
	Vec3d operator * (float);

	Vec3d& operator *= (const Mat4x4&);
	Vec3d operator * (const Mat4x4&);
};

#endif

