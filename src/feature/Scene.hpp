#ifndef SCENE_HPP
#define SCENE_HPP

#include "../feature/Object.hpp"
#include "../feature/Camera.hpp"
#include "../../src/managers/FileManager.hpp"



class Scene {
	static Scene* instancePtr;

	Camera camera;
	float width, height, a, viewAngle, znear, zfar;

	sf::Clock internalClock;


	Scene(float = 1470, float = 1080, float = acos(-1) * 0.5f, float = 1.0f, float = 100.f);
public:
	bool editMode;
	std::string filePath;
	std::vector<Object> objects;
	std::vector<Object::triangle> viewTriangles, triangles;
	std::vector<Vec3d> vertices;

	// std::vector<int> triangleObjectIdx, triangleIdx, vertexIdx;

	static Scene* getInstance() {
		if (instancePtr == nullptr)
			instancePtr = new Scene();	
		return instancePtr;
	}
	void init(std::string, bool = false);
	void save();
	void updateView();
	void drawTo(sf::RenderWindow&);
	void handleEvent(sf::Event);
	void handleClickedTriangle(sf::Event);
	bool triangleClicked(Object::triangle, sf::Event);
};

#endif