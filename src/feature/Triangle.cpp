#include "Triangle.hpp"
#include "Object.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

auto drawLine = [&](sf::Vector2f p1, sf::Vector2f p2, sf::Color lineColor, sf::RenderWindow& window) {
	float width = window.getSize().x;
	float height = window.getSize().y;

	sf::Vertex line[] = {
		sf::Vertex(p1),
		sf::Vertex(p2)
	};

	line[0].color = lineColor;
	line[1].color = lineColor;

	window.draw(line, 2, sf::Lines);
};

Triangle::Triangle() {
	this -> setPointCount(3);
}

Triangle::Triangle(Object& o, Object::face& f, sf::RenderWindow& window) {
	this -> setPointCount(3);
	
	float width = window.getSize().x;
	float height = window.getSize().y;

	std::vector<int> pointx(3);
	std::vector<int> pointy(3);

	for (int index = 0; index < 3; index++) {
		pointx[index] = (o.viewVertices[f.idx[index]].x + 1) * width * 0.5f;
		pointy[index] = (o.viewVertices[f.idx[index]].y + 1) * height * 0.5f;
	}

	this -> setPoint(0, sf::Vector2f(pointx[0], pointy[0]));
	this -> setPoint(1, sf::Vector2f(pointx[1], pointy[1]));
	this -> setPoint(2, sf::Vector2f(pointx[2], pointy[2]));
}

void Triangle::drawTo(sf::RenderWindow& window) {
	std::vector<sf::Vector2f> Points(3);
	for (int p = 0; p < 3; p++) {
		Points[p] = this -> getPoint(p);
	}
	sf::Color outlineColor = this -> getOutlineColor();

	window.draw(*this); /// For the triangle fill color
	drawLine(Points[0], Points[1], outlineColor, window);
	drawLine(Points[0], Points[2], outlineColor, window);
	drawLine(Points[1], Points[2], outlineColor, window);
}