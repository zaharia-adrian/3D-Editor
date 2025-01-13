#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window, float width, float height, float offsetLeft) :
    width(width),
    height(height),
    offsetLeft(offsetLeft),
    posX(offsetLeft + (width - viewWidth) / 2.0f),
    posY((width - viewWidth) / 2.0f + 30),
    paintColor(sf::Color::White)
{
    scene = Scene::getInstance();
    home = Home::getInstance(window);

    ///menu background
    menuBackground = sf::RectangleShape({ width, height });
    menuBackground.setPosition({ offsetLeft, 0.0f });
    menuBackground.setFillColor(ColorManager::secondary);

    ///view backgound
    viewBackground = sf::RectangleShape({ viewWidth, viewHeight });
    viewBackground.setPosition({ posX, posY });
    viewBackground.setFillColor(ColorManager::primary);

    menuButtons = {
        Button("Close", { 150, 40 }, { 1345, 25 }, 20, ColorManager::secondary, ColorManager::light, [&]() {
            if (Modal::getOkDialog(window, "Do you want to save the changes?")) {
                FileManager::saveSceneToFile(scene->filePath.c_str());
            }
            scene->saveAndClose(window);
            home->update();
            home->homePageView = true;
        }),
        Button("Edit mode", { 150, 40 }, { 1345, 75 }, 20, ColorManager::secondary, ColorManager::light, [&]() {
            scene->editMode = !scene->editMode;
            if (scene->editMode) {
                scene->paintMode = false;
                window.setMouseCursorVisible(true);
            }
        }),
        Button("Select mode", { 150, 40 }, { 1345, 125 }, 20, ColorManager::secondary, ColorManager::light, [&]() {
            scene->selectMode = !scene->selectMode;
        }),
        Button("Paint mode", { 150, 40 }, { 1345, 175 }, 20, ColorManager::secondary, ColorManager::light, [&]() {
            scene->paintMode = !scene->paintMode;
            scene->editMode = false;
            if (scene->paintMode) window.setMouseCursorVisible(false);
            else window.setMouseCursorVisible(true);
        }),
        Button("Add object", { 120, 30 }, { 1775, 15 }, 18, ColorManager::primary, ColorManager::light, [&]() {
            if (Modal::addNewObjectDialog(window,"Add new object:")) {
                updateMenu(window);
            }
        }),
        /// additional menu buttons would be added here
    };

    objectProprieties = {/// doesnt look good, has to be changed
        ///translate
        InputBox("X",{1520 + 30, 505},0,[&](float delta) {
            translate(Vec3d(delta, 0, 0));
        }),
        InputBox("Y",{1520 + 130, 505},0,[&](float delta) {
            translate(Vec3d(0, delta,0));
        }),
        InputBox("Z",{1520 + 230, 505},0,[&](float delta) {
            translate(Vec3d(0, 0,delta));
        }),
            ///rotate
            InputBox("X",{1520 + 30, 575},0,[&](float delta) {
                rotate(Vec3d(delta, 0, 0));
            }),
            InputBox("Y",{1520 + 130, 575},0,[&](float delta) {
                rotate(Vec3d(0, delta, 0));
            }),
            InputBox("Z",{1520 + 230, 575},0,[&](float delta) {
                rotate(Vec3d(0, 0,delta));
            }),
            ///scale
            InputBox("X",{1520 + 30, 645},0,[&](float delta) {
                scale(Vec3d(delta, 0, 0));
            }),
            InputBox("Y",{1520 + 130, 645},0,[&](float delta) {
                scale(Vec3d(0, delta, 0));
            }),
            InputBox("Z",{1520 + 230, 645},0,[&](float delta) {
                scale(Vec3d(0, 0,delta));
            }),
    };
    vertexProprieties = {/// doesnt look good, has to be changed
        ///translate
        InputBox("X",{1520 + 30, 505},0,[&](float delta) {
            translate(Vec3d(delta, 0, 0));
        }),
        InputBox("Y",{1520 + 130, 505},0,[&](float delta) {
            translate(Vec3d(0, delta,0));
        }),
        InputBox("Z",{1520 + 230, 505},0,[&](float delta) {
            translate(Vec3d(0, 0,delta));
        })
    };
    menuColors = {
        Button("Red", { 90, 35 }, { 1520 + 30, 505 }, 20, sf::Color::Red, ColorManager::dark, [&]() {
            paintColor = sf::Color::Red;
        }, true),
        Button("Green", { 90, 35 }, { 1520 + 130, 505 }, 20, sf::Color::Green, ColorManager::dark, [&]() {
            paintColor = sf::Color::Green;
        }, true),
        Button("Blue", { 90, 35 }, { 1520 + 230, 505 }, 20, sf::Color::Blue, ColorManager::dark, [&]() {
            paintColor = sf::Color::Blue;
        }, true),
        Button("Magenta", { 90, 35 }, { 1520 + 30, 550 }, 20, sf::Color::Magenta, ColorManager::dark, [&]() {
            paintColor = sf::Color::Magenta;
        }, true),
        Button("Yellow", { 90, 35 }, { 1520 + 130, 550 }, 20, sf::Color::Yellow, ColorManager::dark, [&]() {
            paintColor = sf::Color::Yellow;
        }, true),
        Button("Cyan", { 90, 35 }, { 1520 + 230, 550 }, 20, sf::Color::Cyan, ColorManager::dark, [&]() {
            paintColor = sf::Color::Cyan;
        }, true),
        Button("White", { 90, 35 }, { 1520 + 30, 595 }, 20, sf::Color::White, ColorManager::dark, [&]() {
            paintColor = sf::Color::White;
        }, true),
        Button("Gray", { 90, 35 }, { 1520 + 130, 595 }, 20, sf::Color(128, 128, 128), ColorManager::dark, [&]() {
            paintColor = sf::Color(128, 128, 128);
        }, true),
        Button("Black", { 90, 35 }, { 1520 + 230, 595 }, 20, sf::Color::Black, ColorManager::dark, [&]() {
            paintColor = sf::Color::Black;
        }, true)
    };
    
    updateMenu(window);
};

void Menu::translate(Vec3d& v) { /// would be added more functionality
    if (scene->editMode) {
        for (Object& o : scene->objects)
            o.translateVertices(v);
    }
    else {
        for (Object& o : scene->objects)
            if (o.isSelected)
                o.translate(v);
    }
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

    if(scene->editMode)
        for (InputBox& i : vertexProprieties) i.handleEvent(window, event);
    else
        for (InputBox& i : objectProprieties) i.handleEvent(window, event);

    if (scene->paintMode)
        for (Button& b : menuColors) b.handleEvent(window, event);

    switch (event.type) {
    case sf::Event::MouseWheelScrolled:
        if (posX <= mouseX && mouseX <= posX + viewWidth && posY <= mouseY && mouseY <= posY + viewHeight) {
            viewOffset -= event.mouseWheelScroll.delta * scrollSpeed;
            viewOffset = std::max(0.0f, std::min(viewOffset, objectsListHeight)); ///makes sure 0 <= viewOffset <= objectsListHeight
        }
        break;
    }

}

void Menu::updateMenu(sf::RenderWindow &window) {
    objectsListItems.clear();

    for (int idx = 0; idx < scene->objects.size(); ++idx) {

        std::string objectName = scene->objects[idx].name;
        if (objectName == "") objectName = "Object " + std::to_string(idx);

        sf::Vector2f pos(2 * boxMargin, 2 * boxMargin + objectsListItems.size()/3 * (boxHeight + boxMargin));
        sf::Vector2f size(boxWidth, boxHeight);

        sf::Vector2f sizeBtn = { 60, boxHeight - 10 };
        sf::Vector2f posEdit = { pos.x + size.x + 5, pos.y + 5};
        sf::Vector2f posDelete = { pos.x + size.x + sizeBtn.x + 10, pos.y +5};

        objectsListItems.emplace_back(objectName, size, pos, 21, ColorManager::light, ColorManager::dark, [idx, this]() {
            scene->objects[idx].isSelected = !scene->objects[idx].isSelected;
        });

        objectsListItems.emplace_back("edit", sizeBtn, posEdit, 21, ColorManager::light, ColorManager::dark, [idx, &window, this]() {
            std::string newObjectName = scene->objects[idx].name;
            if (Modal::getNameDialog(window, "Enter new name:", newObjectName)) {
                scene->objects[idx].name = newObjectName;
            }
        });
        objectsListItems.emplace_back("delete", sizeBtn, posDelete, 21, ColorManager::light, ColorManager::dark, [idx,&window, this]() {
            if (Modal::getOkDialog(window, "Are you sure you want to delete " + scene->objects[idx].name + "?")) {
                scene->deleteObject(idx);
            }
        });
    }
}

void Menu::drawTo(sf::RenderWindow& window) {

    updateMenu(window); ///should be moved to scene class, when the objects array changes
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

    scene->menuPaintColor = paintColor;

    sf::Text txt;
    txt.setFont(*FontManager::getInstance());
    txt.setCharacterSize(18);
    txt.setFillColor(ColorManager::dark);

    if (!scene->paintMode) {
        txt.setString("Translate");
        txt.setPosition({ 1520 + 30, 480 });
        window.draw(txt);
    }
    else {
        txt.setString("Color Palette");
        txt.setPosition({ 1520 + 30, 480 });
        window.draw(txt);
    }

    if (!scene->editMode && !scene->paintMode) {
        txt.setString("Rotate");
        txt.setPosition({ 1520 + 30, 550 });
        window.draw(txt);

        txt.setString("Scale");
        txt.setPosition({ 1520 + 30, 620 });
        window.draw(txt);
    }
    
    if (!scene->paintMode) {
        if (scene->editMode)
            for (InputBox& i : vertexProprieties) i.drawTo(window);
        else
            for (InputBox& i : objectProprieties) i.drawTo(window);
    }
    else {
        for (Button& b : menuColors) b.drawTo(window);
    }
}


