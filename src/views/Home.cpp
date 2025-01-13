#include "Home.hpp"


Home *Home::instancePtr = nullptr;
Home::Home(sf::RenderWindow &window) {
	homePageView = true;
	changedView = true;
	scene = Scene::getInstance();
	homeButtons = {
		Button("New project", {150,40},{335,200},21, ColorManager::primary, ColorManager::light, [&]() {
			std::string fileName;
			if (Modal::getNameDialog(window, "Enter new project name:", fileName)) {
				scene->init("../../../localProjects/" + fileName + ".obj", true);
				homePageView = false;
				changedView = true;

			}
		}),
		Button("Open project", {150,40},{495,200},21, ColorManager::primary, ColorManager::light, [&]() {
			std::string filePath;
			if (FileManager::selectFileDialog(filePath)) {
				if (FileManager::loadSceneFromFile(filePath)) {
					scene->updateView();
					homePageView = false;
					changedView = true;
				}
			}
		}),
	};
	update();
}
void Home::update() {
	filesListItems.clear();
	sf::Vector2f size(400,50);
	
	for (std::string &fileName : FileManager::getFilesList()) {
		sf::Vector2f pos(335, 300 + filesListItems.size() * (size.y + 10));
		filesListItems.emplace_back(fileName.substr(0, fileName.size() - 4), size, pos, 30, ColorManager::light, ColorManager::primary, [fileName, this]() {
			scene->init("../../../localProjects/" + fileName);
			homePageView = false;
			changedView = true;
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
	title.setColor(ColorManager::light);
	window.draw(title);

	for (Button& b : homeButtons)
		b.drawTo(window);
	for (Button& b : filesListItems)
		b.drawTo(window);
}
