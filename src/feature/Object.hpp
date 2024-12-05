#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <iostream>
#include <vector>
#include <SFML/Graphics/Color.hpp>

#include "../../src/utils/Vec3d.hpp"
#include "../../src/utils/Mat4x4.hpp"

class Object {
	struct face {
		int idx[3];
		sf::Color c;
		face(int idx0, int idx1, int idx2, const sf::Color& _c){
			idx[0] = idx0; idx[1] = idx1; idx[2] = idx2;
			c = _c;
		}
	};
	std::vector<face> faces;
	std::vector<Vec3d> vertices;
	Mat4x4 world;

	bool idxInBounds(int idx);
public:
	
	Object();
	void addFace(int, int, int, sf::Color);
	void addVertex(const Vec3d&);
	void addVertex(float, float, float, float);

};

#endif