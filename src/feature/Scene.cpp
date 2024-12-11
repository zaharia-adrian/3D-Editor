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
	auto drawLine = [&](Vec3d v1, Vec3d v2) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f((v1.x + 1) * width * 0.5f,(1 + v1.y) * height * 0.5f)),
			sf::Vertex(sf::Vector2f((v2.x + 1) * width * 0.5f,(1 + v2.y) * height * 0.5f))
		};
		//std::cout << v1.x << ' ' << v1.y << " | " << v2.x << ' ' << v2.y << '\n';
		window.draw(line, 2, sf::Lines);
		};

	
	for (Object &o : objects) {
		for (int ind = 0;ind < o.vertices.size();ind++) {
			o.viewVertices[ind]  = o.vertices[ind] * view;
		}
		for (Object::face &f : o.faces) {

			std::vector<int> pointx(3);
			std::vector<int> pointy(3);

			for (int index = 0; index < 3; index++) {
				pointx[index] = (o.viewVertices[f.idx[index]].x + 1) * width * 0.5f;
				pointy[index] = (o.viewVertices[f.idx[index]].y + 1) * height * 0.5f;
			}

			sf::ConvexShape triangle;
			triangle.setPointCount(3);
			triangle.setPoint(0, sf::Vector2f(pointx[0], pointy[0]));
			triangle.setPoint(1, sf::Vector2f(pointx[1], pointy[1]));
			triangle.setPoint(2, sf::Vector2f(pointx[2], pointy[2]));
			triangle.setOutlineColor(sf::Color::Red);
			triangle.setOutlineThickness(1);
			triangle.setFillColor(sf::Color::Black);
			window.draw(triangle);

			/*
			drawLine(o.viewVertices[f.idx[0]], o.viewVertices[f.idx[1]]);
			drawLine(o.viewVertices[f.idx[0]], o.viewVertices[f.idx[2]]);
			drawLine(o.viewVertices[f.idx[1]], o.viewVertices[f.idx[2]]);
			*/
		}
	}
}
