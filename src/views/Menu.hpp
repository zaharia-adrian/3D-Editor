#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
class Menu {
	float width, height, offsetLeft;

public:
	Menu(float, float, float);
	void drawTo(sf::RenderWindow &) const;
};

#endif