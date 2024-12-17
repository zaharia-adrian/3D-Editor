#include "Object.hpp"


Object::Object() {
	name = "";
	isSelected = false;
	updateWorldMat();
};

Mat4x4 Object::getWorldMat()const {
	return world;
};

bool Object::idxInBounds(int idx) const {
	return (0 <= idx && idx <= vertices.size() - 1);
};

void Object::addTriangle(int idx0, int idx1, int idx2, sf::Color _c) {
	if (idxInBounds(idx0) && idxInBounds(idx1) && idxInBounds(idx2))
		triangles.emplace_back(idx0, idx1, idx2, _c);
};

void Object::addVertex(const Vec3d& v) {
	vertices.emplace_back(v);
};

void Object::addVertex(float x, float y, float z, float w) {
	vertices.emplace_back(x, y, z, w); 
};

void Object::updateWorldMat() {
	world = Mat4x4::translation(pos.x, pos.y, pos.z);
	world *= Mat4x4::rotationX(rot.x);
	world *= Mat4x4::rotationY(rot.y);
	world *= Mat4x4::rotationZ(rot.z);
}




    

