
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
			case sf::Event::TextEntered:
				if (event.text.unicode == '\b') {
					if (!name.empty()) name.pop_back();
				}
				else if (event.text.unicode < 128) {
					name += static_cast<char>(event.text.unicode);
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
	modal.setPosition({560,290});


	sf::Text title;
	title.setString(_title);
	title.setFont(*FontManager::getInstance());
	title.setCharacterSize(24);
	title.setPosition({600,400});
	title.setColor(ColorManager::dark);
	
	while (open) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
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



