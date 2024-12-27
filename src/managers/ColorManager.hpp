#ifndef COLORMANAGER_HPP
#define COLORMANAGER_HPP

#include <SFML/Graphics.hpp>
class ColorManager {

public:
	static sf::Color primary;
	static sf::Color secondary;
	static sf::Color tertiary;

	static sf::Color light;
	static sf::Color dark;

	static sf::Color success;
	static sf::Color danger;
};
#endif