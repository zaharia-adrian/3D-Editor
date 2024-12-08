#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vec3d.hpp"
#include <iomanip>

class Quaternion {
public:
	float x, y, z, w;

	Quaternion();
	Quaternion(const Vec3d&, float);
	Quaternion(float, float, float, float);

	void print() const;
	Quaternion& normalize();
	Quaternion conjugate();
	Quaternion operator *(const Vec3d&);
	Quaternion operator *(const Quaternion&);
};

#endif