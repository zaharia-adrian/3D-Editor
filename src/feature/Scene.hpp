#ifndef SCENE_HPP
#define SCENE_HPP

#include "../feature/Object.hpp"
#include "../feature/Camera.hpp"
#include "../../src/managers/FileManager.hpp"
#include "../../src/ui/Modal.hpp"



class Scene {
	static Scene* instancePtr;

	Camera camera;
	float width, height, a, viewAngle, znear, zfar;

	sf::Clock internalClock;

	Scene(float = 1520, float = 1080, float = acos(-1) * 0.5f, float = 1.0f, float = 1000.f);
public:
	
	bool editMode, selectMode;
	std::string filePath;
	std::vector<Object> objects;
	std::vector<Object::triangle> viewTriangles, triangles;
	std::vector<Object::vertex> vertices, cVertices;

	// std::vector<int> triangleObjectIdx, triangleIdx, vertexIdx;

	static Scene* getInstance() {
		if (instancePtr == nullptr)
			instancePtr = new Scene();	
		return instancePtr;
	}
	void init(std::string, bool = false);
	void saveAndClose(sf::RenderWindow &);

	void deleteObject(int idx);

	void updateView();

	void drawTo(sf::RenderWindow&);
	void handleEvent(sf::RenderWindow &, sf::Event);

	void handleClickedTriangle(sf::Event);
	bool handleClickedVertex(sf::Event);
	bool triangleClicked(Object::triangle, sf::Event);
	
};

#endif