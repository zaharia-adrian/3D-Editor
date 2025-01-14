#ifndef CUSTOMCURSOR_HPP
#define CUSTOMCURSOR_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/feature/Scene.hpp"

class CustomCursor {
public:
	CustomCursor(std::string);
	void update(sf::RenderWindow&);
	void drawTo(sf::RenderWindow&);

private:
	sf::Image cursorImage;
	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
};

#endif