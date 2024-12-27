#include "Home.hpp"


Home *Home::instancePtr = nullptr;
Home::Home() {
	homePageView = true;
	scene = Scene::getInstance();
	homeButtons = {
		Button("New project", {130,30},{335,200},21,sf::Color(128, 128, 128), sf::Color::Black, [&]() {
			scene->init("../../../localProjects/", true); /// + fileName (implement naming modal window)
			homePageView = false;
		}),
		Button("Open project", {130,30},{475,200},21,sf::Color(128, 128, 128), sf::Color::Black, [&]() {
			if (FileManager::loadSceneFromFileDialog()) {
				scene->updateView();
				homePageView = false;
			}
		}),
	};
	update();
}
void Home::update() {
	filesListItems.clear();
	sf::Vector2f size(400,50);
	
	for (std::string &fileName : FileManager::getFilesList()) {
		sf::Vector2f pos(345, 300 + filesListItems.size() * (size.y + 10));
		filesListItems.emplace_back(fileName.substr(0, fileName.size() - 4), size, pos, 30, sf::Color(36,36,36), sf::Color::White, [fileName, this]() {
			scene->init("../../../localProjects/" + fileName);
			homePageView = false;
		});
	}
}

void Home::handleEvent(sf::RenderWindow& window, sf::Event event) {
	for (Button& b : homeButtons)
		b.handleEvent(window, event);
	for (Button& b : filesListItems)
		b.handleEvent(window, event);
}


void Home::drawTo(sf::RenderWindow& window) {
	sf::Text title("3D Editor", *FontManager::getInstance(), 75);
	title.setPosition(335, 75);
	title.setColor(sf::Color::White);
	window.draw(title);

	for (Button& b : homeButtons)
		b.drawTo(window);
	for (Button& b : filesListItems)
		b.drawTo(window);
}
