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
		int objectIdx, triangleIdx;
		bool isSelected;
		triangle(int idx0, int idx1, int idx2, int _objectIdx, int _triangleIdx, const sf::Color _c = sf::Color::Green, bool _isSelected = false){
			idx[0] = idx0; idx[1] = idx1; idx[2] = idx2;
			c = _c;
			objectIdx = _objectIdx;
			triangleIdx = _triangleIdx;
			isSelected = _isSelected;
		}
	};
	struct vertex {
		Vec3d v;
		int objectIdx, vertexIdx;
		bool isSelected;
		vertex(Vec3d _v, int _objectIdx, int _vertexIdx, bool _isSelected = false) {
			v = _v;
			objectIdx = _objectIdx;
			vertexIdx = _vertexIdx;
			isSelected = _isSelected;
		}
	};
	std::vector<triangle> triangles;
	std::vector<vertex> vertices;
	Mat4x4 world;
	Vec3d pos, rot, scl;
	std::string name;
	sf::Color color;
	bool isSelected;

	bool idxInBounds(int idx) const;
	
	Object();
	Mat4x4 getWorldMat() const;
	void addTriangle(int, int, int, int, int, sf::Color = sf::Color::Green);
	void addVertex(float, float, float, int, int);

	void translate(Vec3d);
	void scale(Vec3d);
	void rotate(Vec3d);

	void updateWorldMat();

};

#endif