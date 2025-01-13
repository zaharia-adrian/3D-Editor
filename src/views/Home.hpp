#ifndef HOME_HPP
#define HOME_HPP

#include "../../src/ui/Button.hpp"
#include "../../src/ui/Modal.hpp"
#include "../../src/managers/FileManager.hpp"
#include "../../src/managers/FontManager.hpp"
#include "../../src/managers/ColorManager.hpp"
#include "../../src/feature/Scene.hpp"

class Home {
	static Home *instancePtr;

	Scene *scene;
	std::vector<Button> filesListItems, homeButtons;

	Home(sf::RenderWindow &);

public:
	static Home* getInstance(sf::RenderWindow &window) {
		if (instancePtr == nullptr)
			instancePtr = new Home(window);
		return instancePtr;
	}

	bool homePageView, changedView;

	void update();
	void handleEvent(sf::RenderWindow&, sf::Event);
	void drawTo(sf::RenderWindow&);
};
#endif