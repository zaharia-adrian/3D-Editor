#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../../src/managers/FontManager.hpp"
#include "../../src/managers/ColorManager.hpp"



class Button {
public:
    Button();
    Button(std::string, sf::Vector2f, sf::Vector2f, int, sf::Color, sf::Color, std::function<void()> = [&](){}, bool = false);

    void setBackColor(sf::Color);
    void setTextColor(sf::Color);
    void setPosition(sf::Vector2f);
    void drawTo(sf::RenderWindow&);
    void drawTo(sf::RenderTexture&);
    void press();
    void release();
    void switchOnOff();
    bool handleEvent(sf::RenderWindow&, sf::Event, sf::Vector2f = sf::Vector2f());

    bool isPressed();
    bool isSwitchedOn();
    bool isMouseOver(sf::RenderWindow&, sf::Vector2f = sf::Vector2f());

    void setCallback(std::function<void()> = [&]() {});
private:
    std::function<void()> onClick;
    sf::RectangleShape button;
    sf::Text text;
    sf::Color bgColor;
    bool pressed;
    bool switchedOn;
    bool isColorBox;
};  

#endif