#include "Vec3d.hpp"
#include <iostream>


Vec3d::Vec3d() {
	x = y = z = w = 0;
}

Vec3d::Vec3d(float _x, float _y, float _z, float _w = 1) {
	x = _x, y = _y, z = _z, w = _w;
}

void Vec3d::print() { /// for debugging :))
	std::cout << '(' << this->x << ", " << this->y << ", " << this->z <<", "<<this->w<<")\n";
}

float Vec3d::length() const{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vec3d& Vec3d::normalise() {
	*this /= this->length();
	return *this;
}

float Vec3d::dotProd(const Vec3d &v1, const Vec3d &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z + v2.z;
}

Vec3d Vec3d::crossProd(const Vec3d &v1, const Vec3d &v2) {
	Vec3d v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.x * v2.z - v1.z * v2.x;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

Vec3d& Vec3d::operator = (const Vec3d& other) {
	this->x = other.x; this->y = other.y, this->z = other.z, this->w = other.w;
	return *this;
}

Vec3d& Vec3d::operator += (const Vec3d& other) {
	this->x += other.x, this->y += other.y, this->z += other.z;
	return *this;
}
Vec3d& Vec3d::operator -= (const Vec3d& other) {
	this->x -= other.x,	this->y -= other.y,	this->z -= other.z;
	return *this;
}

Vec3d& Vec3d::operator *= (float c) {
	this->x *= c, this->y *=c, this->z *=c;
	return *this;
}

Vec3d& Vec3d::operator /= (float c) {
	this->x /= c, this->y /= c, this->z /= c;
	return *this;
}

Vec3d& Vec3d::operator *=(const Mat4x4 &m) {
	Vec3d v;

	v.x = this->x * m.m[0][0] + this->y * m.m[1][0] + this->z * m.m[2][0] + m.m[3][0];
	v.y = this->x * m.m[0][1] + this->y * m.m[1][1] + this->z * m.m[2][1] + m.m[3][1];
	v.z = this->x * m.m[0][2] + this->y * m.m[1][2] + this->z * m.m[2][2] + m.m[3][2];
	v.w = this->x * m.m[0][3] + this->y * m.m[1][3] + this->z * m.m[2][3] + m.m[3][3];
	
	if (v.w != 0.0f) v /= v.w;

	*this = v;
	return *this;
}