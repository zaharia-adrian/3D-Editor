#include "Menu.hpp"

Menu::Menu(float width, float height, float offsetLeft) :
    width(width),
    height(height),
    offsetLeft(offsetLeft),
    posX(offsetLeft + (width - viewWidth) / 2.0f),
    posY((width - viewWidth) / 2.0f)
{
    scene = Scene::getInstance();

    ///menu background
    menuBackground = sf::RectangleShape({ width, height });
    menuBackground.setPosition({ offsetLeft, 0.0f });
    menuBackground.setFillColor(sf::Color(128, 128, 128));

    ///view backgound
    viewBackground = sf::RectangleShape({ viewWidth, viewHeight });
    viewBackground.setPosition({ posX, posY });
    viewBackground.setFillColor(sf::Color(100, 100, 100));

    menuButtons = {
        Button("Edit mode", { 150, 40 }, { 1295, 25 }, 20, sf::Color(128,128,128), sf::Color::Black, [&]() {
        scene->editMode = !scene->editMode;
        }),
            /// additional menu buttons would be added here
    };

    updateMenu();
};

void Menu::handleEvent(sf::RenderWindow& window, sf::Event event) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    if (posX <= mouseX && mouseX <= posX + viewWidth && posY <= mouseY && mouseY <= posY + viewHeight)
        for (Button& b : objectsListItems)
            b.handleEvent(window, event, { posX, posY - viewOffset });

    for (Button& b : menuButtons)
        b.handleEvent(window, event);


    switch (event.type) {
    case sf::Event::MouseWheelScrolled:
        if (posX <= mouseX && mouseX <= posX + viewWidth && posY <= mouseY && mouseY <= posY + viewHeight) {
            viewOffset -= event.mouseWheelScroll.delta * scrollSpeed;
            viewOffset = std::max(0.0f, std::min(viewOffset, objectsListHeight)); ///makes sure 0 <= viewOffset <= objectsListHeight
        }
        break;

    }

}

void Menu::updateMenu() {
    objectsListItems.clear();

    for (int idx = 0; idx < scene->objects.size(); ++idx) {

        std::string objectName = scene->objects[idx].name;
        if (objectName == "") objectName = "Object " + std::to_string(idx);

        sf::Vector2f pos(2 * boxMargin, 2 * boxMargin + objectsListItems.size() * (boxHeight + boxMargin));
        sf::Vector2f size(boxWidth, boxHeight);

        objectsListItems.emplace_back(objectName, size, pos, 21, sf::Color::Blue, sf::Color::Black, [idx, this]() {
            scene->objects[idx].isSelected = !scene->objects[idx].isSelected;
           });
    }
}

void Menu::drawTo(sf::RenderWindow& window) {

    sf::RenderTexture renderTexture;
    renderTexture.create(viewWidth, viewHeight);
    renderTexture.clear(sf::Color::Transparent);


    sf::View scrollView(sf::FloatRect(0, viewOffset, viewWidth, viewHeight));

    renderTexture.setView(scrollView);

    for (Button& b : objectsListItems)
        b.drawTo(renderTexture);

    renderTexture.display();


    sf::Sprite clippedSprite(renderTexture.getTexture());
    clippedSprite.move(posX, posY);


    window.draw(menuBackground);
    window.draw(viewBackground);
    window.draw(clippedSprite);

    for (Button& b : menuButtons)
        b.drawTo(window);
}


