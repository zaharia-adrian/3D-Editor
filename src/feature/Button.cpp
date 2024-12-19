#include "Button.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

Button::Button() {
    pressed = false;
    switchedOn = false;
}

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor, std::function<void()> callback):
    callback(std::move(callback))
{
    text.setString(t);
    text.setColor(textColor);
    text.setCharacterSize(charSize);
    text.setFont(*FontManager::getInstance());

    button.setSize(size);
    button.setFillColor(bgColor);

    pressed = false;
    switchedOn = false;
}


void Button::setBackColor(sf::Color color) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    text.setColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);

    float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
    float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
    text.setPosition({ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

void Button::press() {
    pressed = true;
    callback();
}

void Button::release() {
    pressed = false;
}

void Button::switchOnOff() {
    switchedOn = 1 - switchedOn;
}

bool Button::isPressed() {
    if (pressed) return true;
    return false;
}

void Button::handleEvent(sf::RenderWindow& window, sf::Event event) {
    switch (event.type) {
    case sf::Event::MouseMoved:
        if (this->isMouseOver(window)) {
            if (!this->isPressed()) {
                this->setBackColor(sf::Color::Blue);
            }
        } else {
            this->setBackColor(sf::Color(128, 128, 128));
        }
        break;

    case sf::Event::MouseButtonPressed:
        if (this->isMouseOver(window)) { /// !!! have to implement for the specific button callback
            this->setBackColor(sf::Color::Green);
            this->press();
            Scene *scene = Scene::getInstance();
            scene->editMode = !scene->editMode;
        }
        break;

    case sf::Event::MouseButtonReleased:
        this->release();
        if (this->isMouseOver(window)) {
            this->switchOnOff();
            this->setBackColor(sf::Color::Blue);
        }
        break;
    }
}

bool Button::isSwitchedOn() {
    if (switchedOn) return true;
    return false;
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;

    float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
    float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;    
    }

    return false;
}