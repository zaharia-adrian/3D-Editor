#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include "../feature/Scene.hpp"
#include "../../src/managers/FontManager.hpp"


class Menu {
	Scene *scene;
	float scrollSpeed = 20.0f;
	const float viewWidth = 400;
	const float viewHeight = 500;
	const float boxWidth = 200;
	const float boxHeight = 35;
	const float boxMargin = 7;
	float viewOffset = 0;
	float objectsListHeight = 0;
	float posX, posY;
	float width, height, offsetLeft;
	sf::RectangleShape menuBackground, viewBackground;
	std::vector<bool> showTriangles, showVertices, showObjectProps;

public:
	Menu(float, float, float);
	void handleEvent(sf::Event);
	void drawTo(sf::RenderWindow &) const;
};

#endif