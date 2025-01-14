#ifndef MODAL_HPP
#define MODAL_HPP

#include <SFML/Graphics.hpp>
#include "../../src/ui/Button.hpp"
#include "../../src/managers/FileManager.hpp"

class Modal {
public:
	static bool getNameDialog(sf::RenderWindow&, std::string, std::string&);
	static bool getOkDialog(sf::RenderWindow&, std::string);
	static bool addNewObjectDialog(sf::RenderWindow&, std::string);
	static void errorMessageDialog(sf::RenderWindow&, std::string);

};
#endif