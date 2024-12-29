#include "Object.hpp"


Object::Object():
	scl(1.0f,1.0f,1.0f)
{
	name = "";
	isSelected = false;
	color = sf::Color::Red;
	updateWorldMat();
};

Mat4x4 Object::getWorldMat()const {
	return world;
};

bool Object::idxInBounds(int idx) const {
	return (0 <= idx && idx <= vertices.size() - 1);
};

void Object::addTriangle(int idx0, int idx1, int idx2, int _objectIdx, int _triangleIdx, sf::Color _c) {
	if (idxInBounds(idx0) && idxInBounds(idx1) && idxInBounds(idx2))
		triangles.emplace_back(idx0, idx1, idx2, _objectIdx, _triangleIdx, _c);
};


void Object::addVertex(float x, float y, float z, int _objectIdx, int _vertexIdx) {
	vertices.emplace_back( Vec3d(x, y, z), _objectIdx, _vertexIdx);
};

void Object::translate(Vec3d delta) {
	pos += delta;
	updateWorldMat();
}
void Object::scale(Vec3d delta) {
	scl +=delta;
	updateWorldMat();
}
void Object::rotate(Vec3d delta) {
	rot += delta;
	updateWorldMat();
}

void Object::updateWorldMat() {
	world = Mat4x4::translation(pos.x, pos.y, pos.z);
	world *= Mat4x4::scale(scl.x,scl.y,scl.z);
	world *= Mat4x4::rotationX(rot.x);
	world *= Mat4x4::rotationY(rot.y);
	world *= Mat4x4::rotationZ(rot.z);
}




    

