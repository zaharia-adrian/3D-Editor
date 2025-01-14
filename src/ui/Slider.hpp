#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

class Slider {
public:
    Slider(float, float, float, sf::Color, float, float = 0, float = 255);

    void handleEvent(sf::RenderWindow&, sf::Event&, sf::Color&);
    void updateThumbPosition();
    void updateColor(float);
    void drawTo(sf::RenderWindow&);
    
    float getValue();

private:
    sf::RectangleShape bar;
    sf::CircleShape thumb;
    float minValue, maxValue;
    float value;
    bool isDragging = false;
};

#endif