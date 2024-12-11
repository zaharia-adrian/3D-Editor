#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button();
    Button(std::string, sf::Vector2f, int, sf::Color, sf::Color);

    void setFont(sf::Font&);
    void setBackColor(sf::Color);
    void setTextColor(sf::Color);
    void setPosition(sf::Vector2f);
    void drawTo(sf::RenderWindow&);
    void press();
    void release();
    void switchOnOff();

    bool isPressed();
    bool isSwitchedOn();
    bool isMouseOver(sf::RenderWindow&);
private:
    sf::RectangleShape button;
    sf::Text text;
    bool pressed;
    bool switchedOn;
};

#endif