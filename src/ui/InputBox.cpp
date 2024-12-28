#include "InputBox.hpp"


InputBox::InputBox(std::string _name, sf::Vector2f pos, float _value, std::function<void(float)> _onScroll) :
	isActive(false),
	onScroll(std::move(_onScroll))
{
	setValue(_value);

	box.setSize({100,40});
	box.setPosition(pos);
	box.setFillColor(ColorManager::tertiary);

	text.setFont(*FontManager::getInstance());
	text.setFillColor(ColorManager::primary);
	text.setCharacterSize(21);

	float xPos = pos.x + (box.getLocalBounds().width - text.getLocalBounds().width) / 2 - (text.getLocalBounds().left);
	float yPos = pos.y + (box.getLocalBounds().height - text.getLocalBounds().height) / 2 - (text.getLocalBounds().top);
	text.setPosition({xPos, yPos});
	

	name.setFont(*FontManager::getInstance());
	name.setFillColor(ColorManager::secondary);
	name.setCharacterSize(16);
	name.setPosition({ pos.x + 3, pos.y });
	name.setString(_name);
}

void InputBox::setValue(float _value) {
	value = _value;
	///just to only take 2 decimals ;))
	text.setString((value < 0 ? "- " : "  ") + std::to_string( + abs((int)value)) + "." + std::to_string(abs(((int)(value * 100) % 100))));

	float xPos = box.getPosition().x + (box.getLocalBounds().width - text.getLocalBounds().width) / 2 - (text.getLocalBounds().left);
	float yPos = box.getPosition().y + (box.getLocalBounds().height - text.getLocalBounds().height) / 2 - (text.getLocalBounds().top);
	text.setPosition({ xPos, yPos });
}


void InputBox::handleEvent(sf::RenderWindow& window, sf::Event event) {
	switch (event.type) {
	case sf::Event::MouseWheelScrolled:
		if (isMouseOver(window)) {
			setValue(value + event.mouseWheelScroll.delta * 0.1f);
			onScroll(event.mouseWheelScroll.delta * 0.1f);
		}
		break;
	case sf::Event::MouseMoved:
		if (isMouseOver(window)) {
			text.setFillColor(ColorManager::dark);
		}
		else {
			setValue(0);
			text.setFillColor(ColorManager::secondary);
		}
	default:
		break;
	}
}

bool InputBox::isMouseOver(sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float minX = box.getPosition().x;
	float minY = box.getPosition().y;

	float maxX = minX + box.getLocalBounds().width;
	float maxY = minY + box.getLocalBounds().height;

	if (mouseX < maxX && mouseX > minX && mouseY < maxY && mouseY > minY) {
		return true;
	}
	return false;
}

void InputBox::drawTo(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(name);
	window.draw(text);
}