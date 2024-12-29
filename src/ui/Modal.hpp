#ifndef MODAL_HPP
#define MODAL_HPP

#include <SFML/Graphics.hpp>
#include "../../src/ui/Button.hpp"

class Modal {

public:
	static bool getNameDialog(sf::RenderWindow&, std::string, std::string&);
	static bool getOkDialog(sf::RenderWindow&, std::string);

};
#endif