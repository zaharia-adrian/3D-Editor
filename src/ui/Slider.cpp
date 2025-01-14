#include "Slider.hpp"

Slider::Slider(float x, float y, float width, sf::Color color, float initialValue, float min, float max)
    : minValue(min), maxValue(max), value(initialValue) {

    bar.setPosition(x, y);
    bar.setSize({ width, 10.f });
    bar.setFillColor(color);

    thumb.setRadius(10.f);
    thumb.setOrigin(thumb.getRadius(), thumb.getRadius());
    thumb.setFillColor(sf::Color::White);
    thumb.setOutlineThickness(2.f);
    thumb.setOutlineColor(sf::Color::Black);

    updateThumbPosition();
}

void Slider::handleEvent(sf::RenderWindow& window, sf::Event& event, sf::Color& menuUpdatedColor) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (thumb.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) ||
            bar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            isDragging = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    }

    if (isDragging && event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float newThumbX = static_cast<float>(mousePos.x);

        newThumbX = std::max(bar.getPosition().x, std::min(newThumbX, bar.getPosition().x + bar.getSize().x));

        float normalizedPosition = (newThumbX - bar.getPosition().x) / bar.getSize().x;
        value = minValue + normalizedPosition * (maxValue - minValue);

        updateThumbPosition();
    }

    if (bar.getFillColor() == sf::Color::Red) menuUpdatedColor.r = value;
    if (bar.getFillColor() == sf::Color::Green) menuUpdatedColor.g = value;
    if (bar.getFillColor() == sf::Color::Blue) menuUpdatedColor.b = value;
}

void Slider::updateThumbPosition() {
    float normalizedValue = (value - minValue) / (maxValue - minValue);
    float thumbX = bar.getPosition().x + normalizedValue * bar.getSize().x;
    thumb.setPosition(thumbX, bar.getPosition().y + bar.getSize().y / 2.f);
}

void Slider::updateColor(float colorValue) {
    value = colorValue;
    updateThumbPosition();
}

void Slider::drawTo(sf::RenderWindow& window) {
    window.draw(bar);
    window.draw(thumb);
}

float Slider::getValue() { return value; }