#include "Object.hpp"


Object::Object() {};


bool Object::idxInBounds(int idx) {
	return (0 <= idx && idx <= vertices.size() - 1);
}

void Object::addFace(int idx0, int idx1, int idx2, sf::Color color) {
	if (idxInBounds(idx0) && idxInBounds(idx1) && idxInBounds(idx2)) 
		faces.emplace_back( idx0,idx1,idx2,color);
}
void Object::addVertex(const Vec3d& v) {
	vertices.emplace_back(v);
};

void Object::addVertex(float x, float y, float z, float w = 1) {
	vertices.emplace_back(x, y, z, w);
};
