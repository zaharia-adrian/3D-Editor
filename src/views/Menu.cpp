
#include "Menu.hpp"

Menu::Menu(float width, float height, float offsetLeft) :width(width), height(height), offsetLeft(offsetLeft) {};

void Menu::drawTo(sf::RenderWindow& window) const {
	sf::RectangleShape menu(sf::Vector2f(width, height));
	menu.setPosition(sf::Vector2f(offsetLeft, 0.0f));
	menu.setFillColor(sf::Color(128, 128, 128));
	
	window.draw(menu);
}