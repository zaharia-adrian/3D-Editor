#include "Menu.hpp"

Menu::Menu(float width, float height, float offsetLeft) :
    width(width),
    height(height),
    offsetLeft(offsetLeft),
    posX(offsetLeft + (width - viewWidth) / 2.0f),
    posY((width - viewWidth) / 2.0f)
{
    scene = Scene::getInstance();
    home = Home::getInstance();

    ///menu background
    menuBackground = sf::RectangleShape({ width, height });
    menuBackground.setPosition({ offsetLeft, 0.0f });
    menuBackground.setFillColor(ColorManager::secondary);

    ///view backgound
    viewBackground = sf::RectangleShape({ viewWidth, viewHeight });
    viewBackground.setPosition({ posX, posY });
    viewBackground.setFillColor(ColorManager::primary);

    menuButtons = {
        Button("Edit mode", { 150, 40 }, { 1295, 25 }, 20, ColorManager::secondary, ColorManager::light, [&]() {
            scene->editMode = !scene->editMode;
        }),
        Button("Save and close", { 150, 40 }, { 1295, 75 }, 20, ColorManager::secondary, ColorManager::light, [&]() {
            scene->save();
            home->homePageView = true;
        }),
            /// additional menu buttons would be added here
    };
    
    proprieties = {/// doesnt look good, has to be changed
        ///translate
        InputBox("X",{1470 + 30, 475},0,[&](float delta) {
            translate(Vec3d(delta, 0, 0));
        }),
        InputBox("Y",{1470 + 140, 475},0,[&](float delta) {
            translate(Vec3d(0, delta,0));
        }),
        InputBox("Z",{1470 + 250, 475},0,[&](float delta) {
            translate(Vec3d(0, 0,delta));
        }),
        ///rotate
        InputBox("X",{1470 + 30, 575},0,[&](float delta) {
            rotate(Vec3d(delta, 0, 0));
        }),
        InputBox("Y",{1470 + 140, 575},0,[&](float delta) {
            rotate(Vec3d(0, delta, 0));
        }),
        InputBox("Z",{1470 + 250, 575},0,[&](float delta) {
            rotate(Vec3d(0, 0,delta));
        }),
        ///scale
        InputBox("X",{1470 + 30, 675},0,[&](float delta) {
            scale(Vec3d(delta, 0, 0));
        }),
        InputBox("Y",{1470 + 140, 675},0,[&](float delta) {
            scale(Vec3d(0, delta, 0));
        }),
        InputBox("Z",{1470 + 250, 675},0,[&](float delta) {
            scale(Vec3d(0, 0,delta));
        }),
    };
    
    updateMenu();
};

void Menu::translate(Vec3d& v) { /// would be added more functionality
    for (Object& o : scene->objects)
        if (o.isSelected)
            o.translate(v);
    scene->updateView();
}

void Menu::rotate(Vec3d& v) { /// would be added more functionality
    for (Object& o : scene->objects)
        if (o.isSelected)
            o.rotate(v);
    scene->updateView();
}

void Menu::scale(Vec3d& v) { /// would be added more functionality
    for (Object& o : scene->objects)
        if (o.isSelected)
            o.scale(v);
    scene->updateView();
}

void Menu::handleEvent(sf::RenderWindow& window, sf::Event event) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    if (posX <= mouseX && mouseX <= posX + viewWidth && posY <= mouseY && mouseY <= posY + viewHeight)
        for (Button& b : objectsListItems)
            b.handleEvent(window, event, { posX, posY - viewOffset });

    for (Button& b : menuButtons) b.handleEvent(window, event);
    for (InputBox& i : proprieties) i.handleEvent(window, event);


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

        objectsListItems.emplace_back(objectName, size, pos, 21, ColorManager::light, ColorManager::dark, [idx, this]() {
            scene->objects[idx].isSelected = !scene->objects[idx].isSelected;
           });
    }
}

void Menu::drawTo(sf::RenderWindow& window) {

    updateMenu(); ///should be moved to scene class, when the objects array changes
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

    for (Button& b : menuButtons) b.drawTo(window);

    for (InputBox& i : proprieties) i.drawTo(window);


}


