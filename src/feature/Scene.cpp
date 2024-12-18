#include "Scene.hpp"

Scene* Scene::instancePtr = nullptr;

Scene::Scene(float width, float height, float viewAngle, float near, float far):
	width(width),
	height(height),
	near(near),
	far(far),
	viewAngle(viewAngle),
	editMode(false)
{
	a = width / height;
	updateView();
};



void Scene::updateView() {
	
	vertices.clear();
	triangles.clear();
	viewTriangles.clear();
	std::vector<std::pair<Object::triangle, int>> cViewTriangles,cTriangles;

	for (int i = 0;i < objects.size();i++) {

		int count = vertices.size();

		Mat4x4 mat = camera.getViewMat() * objects[i].getWorldMat();

		for (Vec3d& v : objects[i].vertices)
			vertices.emplace_back(v * mat);

		for (Object::triangle& t : objects[i].triangles) {

			Vec3d line1 = (vertices[t.idx[1] + count] - vertices[t.idx[0] + count]);
			Vec3d line2 = (vertices[t.idx[2] + count] - vertices[t.idx[0] + count]);

			Vec3d normal = line1.crossProd(line2).normalize();
			cTriangles.emplace_back(Object::triangle(t.idx[0] + count, t.idx[1] + count, t.idx[2] + count, t.c), i);
			if (normal.dotProd(vertices[t.idx[0] + count]) < 0)
				cViewTriangles.emplace_back(Object::triangle(t.idx[0] + count, t.idx[1] + count, t.idx[2] + count, t.c), i);
		}
		
	}

	for (Vec3d& v : vertices) v *= Mat4x4::perspectiveProjection(width, height, viewAngle, far, near);

	auto frustumCulling = [&](const std::vector<std::pair<Object::triangle, int>>& i, std::vector<std::pair<Object::triangle, int>>& o) {
		for (const std::pair<Object::triangle, int>& t : i) {
			auto isInsideFrustum = [&](const Vec3d& v)->bool {
				return (v.x <= v.w && v.x >= -v.w &&
					v.y <= v.w && v.y >= -v.w &&
					v.z <= v.w && v.z >= -v.w
					);
			};

			if (isInsideFrustum(vertices[t.first.idx[0]]) ||
				isInsideFrustum(vertices[t.first.idx[1]]) ||
				isInsideFrustum(vertices[t.first.idx[2]])
				)
				o.emplace_back(t);
		}
	};
	frustumCulling(cViewTriangles,viewTriangles);
	frustumCulling(cTriangles, triangles);

	for (Vec3d& v : vertices) v *= Mat4x4::screenTransform(width, height);

	std::sort(viewTriangles.begin(), viewTriangles.end(), [&](std::pair<Object::triangle,int>& t1, std::pair<Object::triangle, int>& t2) {
		float z1 = (vertices[t1.first.idx[0]].z + vertices[t1.first.idx[1]].z + vertices[t1.first.idx[2]].z )/3.0f;
		float z2 = (vertices[t2.first.idx[0]].z + vertices[t2.first.idx[1]].z + vertices[t2.first.idx[2]].z )/3.0f;
		return (z1 > z2);
	});
}

void Scene::handleEvent(sf::Event event) {

	if (event.type == sf::Event::KeyPressed) {
		camera.handleEvent(event);
		updateView();
	}
};

bool Scene::triangleClicked(Object::triangle t, sf::Event e) {
	float mouseX = e.mouseButton.x;
	float mouseY = e.mouseButton.y;

	sf::Vector2f A(vertices[t.idx[0]].x, vertices[t.idx[0]].y);
	sf::Vector2f B(vertices[t.idx[1]].x, vertices[t.idx[1]].y);
	sf::Vector2f C(vertices[t.idx[2]].x, vertices[t.idx[2]].y);
	sf::Vector2f P(mouseX, mouseY);

	// Calculate the area of the full triangle
	float denominator = (B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y);

	// Compute barycentric coordinates
	float lambda1 = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) / denominator;
	float lambda2 = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) / denominator;
	float lambda3 = 1.0f - lambda1 - lambda2;

	// The point is inside the triangle if all barycentric weights are between 0 and 1
	return (lambda1 >= 0 && lambda1 <= 1) &&
		(lambda2 >= 0 && lambda2 <= 1) &&
		(lambda3 >= 0 && lambda3 <= 1);
}

void Scene::handleClickedTriangle(sf::Event e) {
	for (auto sceneTriangle = triangles.rbegin(); sceneTriangle != triangles.rend(); sceneTriangle++) {
		Object::triangle t = sceneTriangle -> first;
		if (triangleClicked(t, e)) {
			objects[sceneTriangle->second].isSelected = !objects[sceneTriangle->second].isSelected;
			break;
		}
	}
}

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

void Scene::drawTo(sf::RenderWindow& window, sf::Clock& transparencyClock) {
	
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
		{{0.0f, 0.0f, 0.1f},Vec3d(0.0f, 0.0f, 1.0f)}, /// near plane
		{{0.0f, 0.0f, far},Vec3d(0.0f, 0.0f, -1.0f)}, /// far plane
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
	Mat4x4 view = Mat4x4::screenTransform(width, height) * Mat4x4::perspectiveProjection(width, height, viewAngle, near, far);

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

	///drawing scene in editMode
	if (editMode) {

		float radius = 5.0f;
		sf::CircleShape circle(radius);
		circle.setOrigin({ radius,radius });
		circle.setFillColor(sf::Color(200, 200, 200));

		for (std::pair<Object::triangle, int>& sceneTriangle : triangles) {
			Object::triangle t = sceneTriangle.first;

			drawLine(vertices[t.idx[0]], vertices[t.idx[1]]);
			drawLine(vertices[t.idx[0]], vertices[t.idx[2]]);
			drawLine(vertices[t.idx[1]], vertices[t.idx[2]]);	

			for (int i = 0;i < 3;i++) {
				circle.setPosition({vertices[t.idx[i]].x,vertices[t.idx[i]].y });
				window.draw(circle);
			}
		}
	}
	else {
		///drawing scene in viewMode
		sf::ConvexShape triangle;
		triangle.setPointCount(3);
		for (std::pair<Object::triangle, int>& sceneTriangle : viewTriangles) {
			Object::triangle t = sceneTriangle.first;

			triangle.setPoint(0, { vertices[t.idx[0]].x, vertices[t.idx[0]].y });
			triangle.setPoint(1, { vertices[t.idx[1]].x, vertices[t.idx[1]].y });
			triangle.setPoint(2, { vertices[t.idx[2]].x, vertices[t.idx[2]].y });
			triangle.setFillColor(objects[sceneTriangle.second].color);
			window.draw(triangle);

			if (objects[sceneTriangle.second].isSelected) {
				drawLine(vertices[t.idx[0]], vertices[t.idx[1]]);
				drawLine(vertices[t.idx[0]], vertices[t.idx[2]]);
				drawLine(vertices[t.idx[1]], vertices[t.idx[2]]);

				/// function that changes the triangle color's alpha
				float elapsed = transparencyClock.getElapsedTime().asSeconds();
				float alpha = 128 + 127 * std::sin(elapsed * 5.0f); // 1 to 255

				objects[sceneTriangle.second].color.a = alpha;
				triangle.setFillColor(objects[sceneTriangle.second].color);

			} else {
				objects[sceneTriangle.second].color.a = 255;
			}
		}
	}

}


