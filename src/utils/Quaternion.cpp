#include "Quaternion.hpp"

Quaternion::Quaternion() {};

Quaternion::Quaternion(float _x, float _y, float _z, float _w){
	x = _x, y = _y, z = _z, w = _w;
};

Quaternion::Quaternion(const Vec3d& v, float theta) {

	float sinVal = sinf(theta * 0.5f);
	float cosVal = cosf(theta * 0.5f);

	x = v.x * sinVal, y = v.y * sinVal, z = v.z * sinVal, w = cosVal;
}

void Quaternion::print() const {
	std::cout <<std::fixed<<std::setprecision(2)<< "( " << x << ' ' << y << ' ' << z << ' ' << w << ")\n";
}

Quaternion Quaternion::conjugate() {
	return Quaternion (-x, -y, -z, w);
}

Quaternion& Quaternion::normalize() {
	float l = sqrtf(x*x + y*y + z*z + w*w);
	x /= l, y /= l, z /= l, w /= l;
	return *this;
}

Quaternion Quaternion::operator *(const Vec3d& v) {
	Quaternion q;
	q.w = -x * v.x - y * v.y - z * v.z;
	q.x =  w * v.x + y * v.z - z * v.y;
	q.y =  w * v.y + z * v.x - x * v.z;
	q.z =  w * v.z + x * v.y - y * v.x;
	return q;
}

Quaternion Quaternion::operator *(const Quaternion& other) {
	Quaternion q;

	q.w = w * other.w - x * other.x - y * other.y - z * other.z;
	q.x = x * other.w + w * other.x + y * other.z - z * other.y;
	q.y = y * other.w + w * other.y + z * other.x - x * other.z;
	q.z = z * other.w + w * other.z + x * other.y - y * other.x;

	return q;
}

