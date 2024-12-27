#ifndef HOME_HPP
#define HOME_HPP

#include "../../src/feature/Button.hpp"
#include "../../src/managers/FileManager.hpp"
#include "../../src/managers/FontManager.hpp"
#include "../../src/feature/Scene.hpp"

class Home {
	static Home *instancePtr;

	Scene *scene;
	std::vector<Button> filesListItems, homeButtons;

	Home();

public:
	static Home* getInstance() {
		if (instancePtr == nullptr)
			instancePtr = new Home();
		return instancePtr;
	}

	bool homePageView;

	void update();
	void handleEvent(sf::RenderWindow&, sf::Event);
	void drawTo(sf::RenderWindow&);
};
#endif