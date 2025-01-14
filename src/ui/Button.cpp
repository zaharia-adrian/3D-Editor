#include "Button.hpp"


Button::Button() {
    pressed = false;
    switchedOn = false;
    isColorBox = false;
}

Button::Button(std::string t, sf::Vector2f size, sf::Vector2f pos, int charSize, sf::Color _bgColor, sf::Color textColor, std::function<void()> onClick, bool colorBox) :
    onClick(std::move(onClick)),
    bgColor(_bgColor)
{

    text.setString(t);
    text.setColor(textColor);
    text.setCharacterSize(charSize);
    text.setFont(*FontManager::getInstance());


    button.setSize(size);
    button.setFillColor(bgColor);

    setPosition(pos);

    pressed = false;
    switchedOn = false;
    isColorBox = colorBox;
}


void Button::setBackColor(sf::Color color) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    text.setColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);

    float xPos = pos.x + (button.getLocalBounds().width - text.getLocalBounds().width) / 2 - (text.getLocalBounds().left);
    float yPos = pos.y + (button.getLocalBounds().height - text.getLocalBounds().height) / 2 - (text.getLocalBounds().top);

    text.setPosition({ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

void Button::drawTo(sf::RenderTexture& renderTexture) {
    renderTexture.draw(button);
    renderTexture.draw(text);
}

void Button::press() {
    pressed = true;
    onClick();
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

bool Button::handleEvent(sf::RenderWindow& window, sf::Event event, sf::Vector2f offset) { /// offset for buttons on renderTexture
    switch (event.type) {
    case sf::Event::MouseMoved:
        if (this->isMouseOver(window, offset)) {
            if (!this->isPressed()) {
                if (!isColorBox) this->setBackColor(ColorManager::tertiary);
            }
        }
        else {
            this->setBackColor(bgColor);
        }
        break;

    case sf::Event::MouseButtonPressed:

        if (this->isMouseOver(window, offset)) {
            if (!isColorBox) this->setBackColor(ColorManager::success);
            this->press();
            return true;
        }
        break;

    case sf::Event::MouseButtonReleased:
        this->release();
        if (this->isMouseOver(window)) {
            this->switchOnOff();
            if (!isColorBox) this->setBackColor(ColorManager::tertiary);
        }
        break;
    }
    return false;
}

bool Button::isSwitchedOn() {
    if (switchedOn) return true;
    return false;
}

bool Button::isMouseOver(sf::RenderWindow& window, sf::Vector2f offset) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = button.getPosition().x + offset.x;
    float btnPosY = button.getPosition().y + offset.y;

    float btnxPosWidth = btnPosX + button.getLocalBounds().width;
    float btnyPosHeight = btnPosY + button.getLocalBounds().height;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }

    return false;
}

void Button::setCallback(std::function<void()> callback) {
    onClick = callback;
}