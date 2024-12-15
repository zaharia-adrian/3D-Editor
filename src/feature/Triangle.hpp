#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <SFML/Graphics.hpp>
#include "Object.hpp"

class Triangle : public sf::ConvexShape {
public:
	Triangle();
	Triangle(Object&, Object::face&, sf::RenderWindow&);

	void drawTo(sf::RenderWindow&);
};

#endif