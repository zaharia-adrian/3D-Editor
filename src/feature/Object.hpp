#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <iostream>
#include <stdio.h>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>


#include "../../src/utils/Vec3d.hpp"
#include "../../src/utils/Mat4x4.hpp"
#include "../../src/feature/Camera.hpp"

class Object {
public:
	struct triangle {
		int idx[3];
		sf::Color c;
		triangle(int idx0, int idx1, int idx2, const sf::Color& _c){
			idx[0] = idx0; idx[1] = idx1; idx[2] = idx2;
			c = _c;
		}
	};
	std::vector<triangle> triangles;
	std::vector<Vec3d> vertices;
	Mat4x4 world;
	Vec3d rot; /// rotation angles
	Vec3d pos; /// position in the scene 
	std::string name;
	bool isSelected;

	bool idxInBounds(int idx) const;
	
	Object();
	Mat4x4 getWorldMat() const;
	void addTriangle(int, int, int, sf::Color = sf::Color::White);
	void addVertex(const Vec3d&);
	void addVertex(float, float, float, float = 1);

	void updateWorldMat();
	
};

#endif