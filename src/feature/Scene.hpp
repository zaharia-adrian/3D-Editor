#ifndef SCENE_HPP
#define SCENE_HPP

#include "../feature/Triangle.hpp"
#include "../feature/Object.hpp"
#include "../feature/Camera.hpp"


class Scene {
	std::vector<Object> objects;
	Mat4x4 projection, view;
	Camera camera;

public:
	Scene(float, float);
	void updateView();
	void draw(sf::RenderWindow&);
	void handleMoveCamera(sf::Event);
	Scene& loadFromFile(char*);

};

#endif