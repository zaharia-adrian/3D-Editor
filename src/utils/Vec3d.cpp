#include "Vec3d.hpp"



Vec3d::Vec3d() {
	x = y = z = w = 0;
}

Vec3d::Vec3d(float _x, float _y, float _z, float _w) :x(_x), y(_y), z(_z), w(_w) {};


void Vec3d::print(std::string str) const { /// for debugging :))
	std::cout <<str<< " (" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")\n";
}

float Vec3d::getLength() const{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

bool Vec3d::isRight(const Vec3d& v1, const Vec3d& v2) const { 
	///returns true if the *this is on the right side of the line determined by the v1 and v2
	///takes into account only the x and y coordinates after they have been transformed to screen space
	return (v2.x - v1.x) * (y - v1.y) - (v2.y - v2.y) * (x - v1.x) >= 0;
}

Vec3d& Vec3d::normalize() {
	*this /= this->getLength();
	return *this;
}

Vec3d& Vec3d::rotate(const Vec3d& v, float theta) {
	Quaternion q(v, theta);
	Quaternion qc = q.conjugate();
	Quaternion w = q * (*this) * qc;
	x = w.x, y = w.y, z = w.z;
	return *this;
}

float Vec3d::dotProd(const Vec3d &other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vec3d Vec3d::crossProd(const Vec3d &other) const {
	Vec3d v;
	v.x = y * other.z - z * other.y;
	v.y = z * other.x - x * other.z;
	v.z = x * other.y - y * other.x;
	return v;
}

Vec3d& Vec3d::operator = (const Vec3d& other) {
	x = other.x; y = other.y, z = other.z, w = other.w;
	return *this;
}

Vec3d Vec3d::operator +(const Vec3d& other) {
	return Vec3d(x + other.x, y + other.y, z + other.z, 1.0f);
}

Vec3d Vec3d::operator -(const Vec3d& other) {
	return Vec3d(x - other.x, y - other.y, z - other.z, 1.0f);
}

Vec3d& Vec3d::operator += (const Vec3d& other) {
	x += other.x, y += other.y, z += other.z;
	return *this;
}
Vec3d& Vec3d::operator -= (const Vec3d& other) {
	x -= other.x,	y -= other.y,	z -= other.z;
	return *this;
}

Vec3d& Vec3d::operator *= (float c) {
	x *= c, y *=c, z *=c;
	return *this;
}
Vec3d Vec3d::operator *(float c) {
	Vec3d v;
	v.x = x * c, v.y = y * c, v.z = z * c;
	return v;
}

Vec3d& Vec3d::operator /= (float c) {
	x /= c, y /= c, z /= c, w = 1;
	return *this;
}

Vec3d& Vec3d::operator *=(const Mat4x4 &m) {
	Vec3d v;

	v.x = x * m.m[0][0] + y * m.m[0][1] + z * m.m[0][2] + w * m.m[0][3];
	v.y = x * m.m[1][0] + y * m.m[1][1] + z * m.m[1][2] + w * m.m[1][3];
	v.z = x * m.m[2][0] + y * m.m[2][1] + z * m.m[2][2] + w * m.m[2][3];
	v.w = x * m.m[3][0] + y * m.m[3][1] + z * m.m[3][2] + w * m.m[3][3];

	if (v.w != 0) v /= v.w;
	*this = v;
	return *this;
}
Vec3d Vec3d::operator *(const Mat4x4& m) {
	Vec3d v;

	v.x = x * m.m[0][0] + y * m.m[0][1] + z * m.m[0][2] + w * m.m[0][3];
	v.y = x * m.m[1][0] + y * m.m[1][1] + z * m.m[1][2] + w * m.m[1][3];
	v.z = x * m.m[2][0] + y * m.m[2][1] + z * m.m[2][2] + w * m.m[2][3];
	v.w = x * m.m[3][0] + y * m.m[3][1] + z * m.m[3][2] + w * m.m[3][3];

	if (v.w != 0.0f) v /= v.w;
	return v;
}