#ifndef SCENE_HPP
#define SCENE_HPP

#include "../feature/Object.hpp"
#include "../feature/Camera.hpp"


class Scene {
	std::vector<Object> objects;
	Camera camera;

public:
	Scene(){};
};

#endif