#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../../src/managers/FontManager.hpp"

class Button {
public:
    Button();
    Button(std::string, sf::Vector2f, int, sf::Color, sf::Color, std::function<void()> = [&](){});

    void setBackColor(sf::Color);
    void setTextColor(sf::Color);
    void setPosition(sf::Vector2f);
    void drawTo(sf::RenderWindow&);
    void press();
    void release();
    void switchOnOff();
    void handleEvent(sf::RenderWindow&, sf::Event);

    bool isPressed();
    bool isSwitchedOn();
    bool isMouseOver(sf::RenderWindow&);
private:
    std::function<void()> callback;
    sf::RectangleShape button;
    sf::Text text;
    bool pressed;
    bool switchedOn;
};  

#endif