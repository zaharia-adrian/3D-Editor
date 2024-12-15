#include "Scene.hpp"

Scene::Scene(float width, float height, float viewAngle, float near, float far):
	width(width),
	height(height),
	near(near),
	far(far),
	viewAngle(viewAngle)
{
	a = width / height;
	updateView();
};

void Scene::updateView() {
	

	viewVertices.clear();
	viewTriangles.clear();

	for (int i = 0;i < objects.size();i++) {

		int count = viewVertices.size();
		Mat4x4 mat = Mat4x4::screenTransform(width, height) * Mat4x4::perspectiveProjection(width, height) * camera.getViewMat() * objects[i].getWorldMat();

		for (Vec3d& v : objects[i].vertices)
			viewVertices.emplace_back(v * mat);
		for (Object::triangle& t : objects[i].triangles)
			viewTriangles.emplace_back( Object::triangle(t.idx[0] + count, t.idx[1] + count, t.idx[2] + count, t.c), i);
	}

	std::sort(viewTriangles.begin(), viewTriangles.end(), [&](std::pair<Object::triangle,int>& t1, std::pair<Object::triangle, int>& t2) {
		float z1 = std::min({ viewVertices[t1.first.idx[0]].z, viewVertices[t1.first.idx[1]].z, viewVertices[t1.first.idx[2]].z });
		float z2 = std::min({ viewVertices[t2.first.idx[0]].z, viewVertices[t2.first.idx[1]].z, viewVertices[t2.first.idx[2]].z });
		return (z1 > z2);
	});
}

void Scene::handleMoveCamera(sf::Event e) {

	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Left) camera.moveLeft();
		if (e.key.code == sf::Keyboard::Right) camera.moveRight();
		if (e.key.code == sf::Keyboard::Up) camera.moveUp();
		if (e.key.code == sf::Keyboard::Down) camera.moveDown();
		if (e.key.code == sf::Keyboard::F) camera.moveForward();
		if (e.key.code == sf::Keyboard::B) camera.moveBackward();
		updateView();
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
			objects.back().addTriangle(idx0 - 1, idx1 - 1, idx2 - 1);
		}
		else if (ch == 'v') {
			fscanf(fptr, "%f %f %f", &x, &y, &z);
			if (objects.empty()) objects.emplace_back();
			objects.back().addVertex(x, y, z);
		}
		else if (ch == 'o') {
			objects.emplace_back();
		}
		else if (ch != '\n') {
			while (getc(fptr) != '\n' && !feof(fptr)); ///ignore the rest of the line and set cursor on the next one
		}
	}
	fclose(fptr);

	updateView();
	return *this;
}

void Scene::drawTo(sf::RenderWindow& window) {
	
	auto drawLine = [&](Vec3d v1, Vec3d v2, sf::Color c = sf::Color::White) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(v1.x, v1.y)),
			sf::Vertex(sf::Vector2f(v2.x, v2.y))
		};
		line[0].color = line[1].color = c;
		window.draw(line, 2, sf::Lines);
		};

	float fov = 1 / tan(viewAngle / 2.0f);
	std::vector<std::vector<Vec3d>> planes = {
		/*{{0.0f, 0.0f, near},Vec3d(0.0f, 0.0f, 1.0f)}, /// near plane
		{{0.0f, 0.0f, far},Vec3d(0.0f, 0.0f, -1.0f)}, /// far plane*/
		{{-a, 0.0f, near},Vec3d(fov / a, 0.0f, 1.0f).normalize()}, /// left plane
		{{a, 0.0f, near},Vec3d(-fov / a, 0.0f, 1.0f).normalize()}, /// right plane
		{{0.0f, -1.0f, near},Vec3d(0.0f, fov, 1.0f).normalize()},///top plane
		{{0.0f, 1.0f, near},Vec3d(0.0f, -fov, 1.0f).normalize()}, /// bottom plane
	};

	auto intersectPlane = [&](int planeIdx, Vec3d& v1, Vec3d& v2) {
		Vec3d coord = planes[planeIdx][0];
		Vec3d normal = planes[planeIdx][1];

		float d1 = normal.dotProd(v1 - coord);
		float d2 = normal.dotProd(v2 - coord);
		float t = d1 / (d1 - d2);
		return (v2 - v1) * t + v1;
	};

	auto clipp = [&](Vec3d& v1, Vec3d& v2) {
		for (int planeIdx = 0;planeIdx < planes.size();planeIdx++) {
			std::vector<Vec3d> inside, outside;
			if (planes[planeIdx][1].dotProd(v1 - planes[planeIdx][0]) >= -1e-5) inside.emplace_back(v1);
			else outside.emplace_back(v1);
			if (planes[planeIdx][1].dotProd(v2 - planes[planeIdx][0]) >= -1e-5) inside.emplace_back(v2);
			else outside.emplace_back(v2);

			if (inside.size() == 1) {
				v1 = inside[0];
				v2 = intersectPlane(planeIdx, inside[0], outside[0]);
			}else if (inside.size() == 0) {
				v1 = Vec3d(), v2 = Vec3d();
				return;
			}
		}
		};

	Mat4x4 mat = camera.getViewMat();
	Mat4x4 view = Mat4x4::screenTransform(width, height) * Mat4x4::perspectiveProjection(width, height);

	///drawing the grid
	Vec3d v1, v2;
	int gridSize = 100;
	for (int l = -gridSize; l <= gridSize; l++) {
		sf::Color c(128,128,128,100-abs(l));
		// X-parallel
		v1 = Vec3d(-gridSize, 0, l) * mat;
		v2 = Vec3d(gridSize, 0, l) * mat;
		clipp(v1, v2);
		drawLine(v1 * view, v2 * view, c);

		// Z-parallel
		v1 = Vec3d(l, 0, -gridSize) * mat;
		v2 = Vec3d(l, 0, gridSize) * mat;
		clipp(v1, v2);
		drawLine(v1 * view, v2 * view, c);
	}

	///drawing the triangles
	for (std::pair<Object::triangle,int> &sceneTriangle : viewTriangles) {
		Object::triangle t = sceneTriangle.first;
		
		sf::ConvexShape triangle;
		triangle.setPointCount(3);
		triangle.setPoint(0, sf::Vector2f(viewVertices[t.idx[0]].x, viewVertices[t.idx[0]].y));
		triangle.setPoint(1, sf::Vector2f(viewVertices[t.idx[1]].x, viewVertices[t.idx[1]].y));
		triangle.setPoint(2, sf::Vector2f(viewVertices[t.idx[2]].x, viewVertices[t.idx[2]].y));
		triangle.setFillColor(sf::Color::Red);

		window.draw(triangle);

		drawLine(viewVertices[t.idx[0]], viewVertices[t.idx[1]]);
		drawLine(viewVertices[t.idx[0]], viewVertices[t.idx[2]]);
		drawLine(viewVertices[t.idx[1]], viewVertices[t.idx[2]]);

	}

}


