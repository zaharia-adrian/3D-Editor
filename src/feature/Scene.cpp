#include "Scene.hpp"

Scene::Scene(float width, float height):camera() {
	projection = Mat4x4::projection(width,height);
	updateView();
};

void Scene::updateView() {
	view = projection * camera.getViewMat();
}

void Scene::handleMoveCamera(sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Left) camera.moveLeft();
		if (e.key.code == sf::Keyboard::Right) camera.moveRight();
		if (e.key.code == sf::Keyboard::Up) camera.moveUp();
		if (e.key.code == sf::Keyboard::Down) camera.moveDown();
		if (e.key.code == sf::Keyboard::F) camera.moveForward();
		if (e.key.code == sf::Keyboard::B) camera.moveBackward();
	}
};

Scene& Scene::loadFromFile(char* filePath) {
	FILE* fptr = fopen(filePath, "r");
	if (fptr == NULL) {
		std::cout << "File not found!";
		return *this;
	}
	char ch;
	int idx0, idx1, idx2;
	float x, y, z;

	while ((ch = fgetc(fptr)) != EOF) {
		if (ch == 'f') {
			fscanf(fptr, "%d %d %d", &idx0, &idx1, &idx2);
			if (objects.empty()) objects.emplace_back();
			objects.back().addFace(idx0 - 1, idx1 - 1, idx2 - 1);
		}
		else if (ch == 'v') {
			fscanf(fptr, "%f %f %f", &x, &y, &z);
			if (objects.empty()) objects.emplace_back();
			objects.back().addVertex(x,y,z);
		}
		else if (ch == 'o') {
			if (!objects.empty()){
				objects.back().viewVertices = std::vector<Vec3d>(objects.back().vertices.size());
				objects.back().update();
			}
			objects.emplace_back();
		}
		else if (ch != '\n') {
			while (getc(fptr) != '\n' && !feof(fptr)); ///ignore the rest of the line and set cursor on the next one
		}
	}
	fclose(fptr);

	objects.back().viewVertices = std::vector<Vec3d>(objects.back().vertices.size());
	objects.back().update();

	return *this;
}

void Scene::draw(sf::RenderWindow& window) {
	updateView();

	float width = window.getSize().x;
	float height = window.getSize().y;
	
	for (Object &o : objects) {
		for (int ind = 0;ind < o.vertices.size();ind++) {
			o.viewVertices[ind]  = o.vertices[ind] * view;
		}
		for (Object::face &f : o.faces) {
			Triangle triangle(o, f, window);
			triangle.setOutlineColor(sf::Color::Red);
			triangle.setFillColor(sf::Color::White);
			triangle.drawTo(window);
		}
	}
}
