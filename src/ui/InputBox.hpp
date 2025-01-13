#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include <iostream>
#include <functional>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "../../src/managers/ColorManager.hpp"
#include "../../src/managers/FontManager.hpp"

class InputBox {
	sf::RectangleShape box;
	sf::Text text;
	sf::Text name;
	float value;
	bool isActive;
	std::function<void(float)> handleValueChange;

	sf::Vector2i lastMousePos;
	bool isDragging;

public:
	InputBox(std::string, sf::Vector2f, float, std::function<void(float)> = [&](float){});

	bool isMouseOver(sf::RenderWindow&);
	void setValue(float);

	bool handleEvent(sf::RenderWindow&, sf::Event);
	void drawTo(sf::RenderWindow&);
};

#endif