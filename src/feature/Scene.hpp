#ifndef SCENE_HPP
#define SCENE_HPP


#include "../feature/Object.hpp"
#include "../feature/Camera.hpp"


class Scene {
	float width, height, a, viewAngle, near, far;
	Camera camera;
	std::vector<Object> objects;
	std::vector<std::pair<Object::triangle, int>> viewTriangles;
	std::vector<Vec3d> viewVertices;


public:
	Scene(float, float, float = acos(-1) * 0.5f, float = 1.0f, float = 100.f);
	void updateView();
	void drawTo(sf::RenderWindow&);
	void handleMoveCamera(sf::Event);
	Scene& loadFromFile(char*);

};

#endif