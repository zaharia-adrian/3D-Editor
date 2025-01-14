
#include "Modal.hpp"




bool Modal::getNameDialog(sf::RenderWindow& window, std::string _title, std::string& name) {

	bool open = true, ok = true;

	Button okBtn("Ok", { 100,40 }, { 1110,730 }, 21, ColorManager::primary, ColorManager::light, [&]() { if(name.size()>0)open = false;});
	Button cancelBtn("Cancel", { 100,40 }, { 1230,730 }, 21, ColorManager::primary, ColorManager::light, [&]() { open = false; ok = false;});

	sf::RectangleShape modal({ 800,500 });
	modal.setFillColor(ColorManager::tertiary);
	modal.setPosition({ 560,290 });

	sf::Text title;
	title.setString(_title);
	title.setFont(*FontManager::getInstance());
	title.setCharacterSize(24);
	title.setPosition({ 600,400 });
	title.setColor(ColorManager::dark);

	sf::RectangleShape inputBg({ 720,50 });
	inputBg.setFillColor(ColorManager::primary);
	inputBg.setPosition({ 600,450 });


	sf::Text inputTxt;
	inputTxt.setFont(*FontManager::getInstance());
	inputTxt.setCharacterSize(24);
	inputTxt.setColor(ColorManager::light);
	inputTxt.setPosition({ 610, 457 });
	
	sf::Clock clock;
	while (open) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return false;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter && name.size()) open = false;
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode == '\b') {
					if (!name.empty()) name.pop_back();
				}
				else if (event.text.unicode < 128) {
					char ch = static_cast<char>(event.text.unicode);
					bool validCh = false;
					if ('a' <= ch && ch <= 'z') validCh = true;
					if ('A' <= ch && ch <= 'Z') validCh = true;
					if ('0' <= ch && ch <= '9') validCh = true;
					if (ch == '_' || ch == '-') validCh = true;
					if (validCh) name += ch;
				}

			case sf::Event::Resized: {
				float width = static_cast<float>(window.getSize().x);
				float height = static_cast<float>(window.getSize().y);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				break;
			}
			}
			okBtn.handleEvent(window, event);
			cancelBtn.handleEvent(window, event);
		}
		if ((int)(clock.getElapsedTime().asSeconds()*1.5f) & 1)
			inputTxt.setString(name);
        else
			inputTxt.setString(name + "|");
	

		window.clear(ColorManager::dark);

		window.draw(modal);
		window.draw(inputBg);
		window.draw(title);
		window.draw(inputTxt);
		okBtn.drawTo(window);
		cancelBtn.drawTo(window);

		window.display();
	}
	return ok;

}


bool Modal::getOkDialog(sf::RenderWindow& window, std::string _title) {
	bool open = true, ok = true;

	Button okBtn("Ok", { 100,40 }, { 1110,730 }, 21, ColorManager::primary, ColorManager::light, [&]() { open = false;});
	Button cancelBtn("Cancel", { 100,40 }, { 1230,730 }, 21, ColorManager::primary, ColorManager::light, [&]() { open = false; ok = false;});

	sf::RectangleShape modal({ 800,500 });
	modal.setFillColor(ColorManager::tertiary);
	modal.setPosition({ 560,290 });


	sf::Text title;
	title.setString(_title);
	title.setFont(*FontManager::getInstance());
	title.setCharacterSize(24);
	title.setPosition({ 600,400 });
	title.setColor(ColorManager::dark);

	while (open) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return false;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter) open = false;
				break;
			case sf::Event::Resized: {
				float width = static_cast<float>(window.getSize().x);
				float height = static_cast<float>(window.getSize().y);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				break;
			}
			}
			okBtn.handleEvent(window, event);
			cancelBtn.handleEvent(window, event);
		}

		window.clear(ColorManager::dark);

		window.draw(modal);
		window.draw(title);
		okBtn.drawTo(window);
		cancelBtn.drawTo(window);

		window.display();
	}
	return ok;

}

bool Modal::addNewObjectDialog(sf::RenderWindow &window, std::string _title) {
	bool open = true, ok = true;

	Button cancelBtn("Cancel", { 100,40 }, { 1230,730 }, 21, ColorManager::primary, ColorManager::light, [&]() { open = false; ok = false;});
	Button newObject("New empty object", { 200,40 }, { 1130,330 }, 21, ColorManager::secondary, ColorManager::dark, [&]() {
		std::string objectName;
		if (Modal::getNameDialog(window, "Enter new object name:", objectName)) {
			Scene* scene = Scene::getInstance();
			scene->objects.emplace_back();
			scene->objects.back().name = objectName;
			open = false;
		}
	});

	sf::RectangleShape modal({ 800,500 });
	modal.setFillColor(ColorManager::tertiary);
	modal.setPosition({ 560,290 });

	sf::Text title;
	title.setString(_title);
	title.setFont(*FontManager::getInstance());
	title.setCharacterSize(24);
	title.setPosition({ 600,330 });
	title.setColor(ColorManager::dark);

	std::string folderPath = "../../../predefinedObjects";
	sf::Vector2f size(200, 35);
	std::vector<Button> predefinedObjectsList;
	for (std::string& fileName : FileManager::getPredefinedObjectsList()) {
		sf::Vector2f pos(600, 380 + predefinedObjectsList.size() * (size.y + 5));
		predefinedObjectsList.emplace_back(fileName.substr(0, fileName.size() - 4), size, pos, 24, ColorManager::light, ColorManager::primary, [fileName, folderPath, &open]() {
			FileManager::loadSceneFromFile(folderPath + '/' + fileName);
			Scene::getInstance()->updateView();
			open = false;
		});
	}
	
	while (open) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return false;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter) open = false;
				break;
			case sf::Event::Resized: {
				float width = static_cast<float>(window.getSize().x);
				float height = static_cast<float>(window.getSize().y);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				break;
			}
			}
			cancelBtn.handleEvent(window, event);
			newObject.handleEvent(window, event);
			for (Button& b : predefinedObjectsList) b.handleEvent(window, event);
		}

		window.clear(ColorManager::dark);

		window.draw(modal);
		window.draw(title);
		newObject.drawTo(window);
		cancelBtn.drawTo(window);
		for (Button& b : predefinedObjectsList) b.drawTo(window);

		window.display();
	}
	return ok;
}


void Modal::errorMessageDialog(sf::RenderWindow& window, std::string _title) {
	bool open = true;

	Button cancelBtn("Cancel", { 100,40 }, { 1230,730 }, 21, ColorManager::primary, ColorManager::light, [&]() { open = false;});

	sf::RectangleShape modal({ 800,500 });
	modal.setFillColor(ColorManager::tertiary);
	modal.setPosition({ 560,290 });


	sf::Text title;
	title.setString(_title);
	title.setFont(*FontManager::getInstance());
	title.setCharacterSize(24);
	title.setPosition({ 600,400 });
	title.setColor(ColorManager::danger);

	while (open) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter) open = false;
				break;
			case sf::Event::Resized: {
				float width = static_cast<float>(window.getSize().x);
				float height = static_cast<float>(window.getSize().y);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				break;
			}
			}
			cancelBtn.handleEvent(window, event);
		}

		window.clear(ColorManager::dark);

		window.draw(modal);
		window.draw(title);

		cancelBtn.drawTo(window);

		window.display();
	}
}

