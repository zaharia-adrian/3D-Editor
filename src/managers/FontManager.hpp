#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics.hpp>

class FontManager : public sf::Font {

	static FontManager* instancePtr;

	FontManager();

public:
	static FontManager* getInstance();
};
#endif