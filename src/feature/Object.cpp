#include "Object.hpp"


Object::Object() {
};


bool Object::idxInBounds(int idx) const{
	return (0 <= idx && idx <= vertices.size() - 1);
}

void Object::addFace(int idx0, int idx1, int idx2, sf::Color _c) {
	if (idxInBounds(idx0) && idxInBounds(idx1) && idxInBounds(idx2)) 
		faces.emplace_back( idx0, idx1, idx2, _c);
}
void Object::addVertex(const Vec3d& v) {
	vertices.emplace_back(v);
};

void Object::addVertex(float x, float y, float z, float w) {
	vertices.emplace_back(x, y, z, w); 
};

void Object::update() {
	/*
	 1 Update the world matrix
	 2 Sort the faces to draw the nearest last
	*/

	Mat4x4 world = Mat4x4::identity();
	world *= Mat4x4::translation(pos.x, pos.y, pos.z);
	world *= Mat4x4::rotationX(rot.x);
	world *= Mat4x4::rotationY(rot.y);
	world *= Mat4x4::rotationZ(rot.z);

	for (int ind = 0; ind < vertices.size();ind++)
		viewVertices[ind] = vertices[ind] * world;
}




    

