#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window, float width, float height, float offsetLeft) :
    width(width),
    height(height),
    offsetLeft(offsetLeft),
    posX(offsetLeft + (width - viewWidth) / 2.0f),
    posY((width - viewWidth) / 2.0f + 30),
    paintColor(sf::Color::White),
    redSlider(1520 + 30, 730, 230, sf::Color::Red, 255),
    greenSlider(1520 + 30, 780, 230, sf::Color::Green, 0),
    blueSlider(1520 + 30, 830, 230, sf::Color::Blue, 0),
    colorPreview({100.f, 100.f})
{
    scene = Scene::getInstance();
    home = Home::getInstance(window);

    ///menu background
    menuBackground = sf::RectangleShape({ width, height });
    menuBackground.setPosition({ offsetLeft, 0.0f });
    menuBackground.setFillColor(ColorManager::secondary);

    ///view background
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
            viewOffset = 0;
            for (int idx = 0; idx < scene->objects.size(); ++idx) {
                scene->objects[idx].showObjectProprieties = false;
            }

            if (scene->editMode) {
                scene->paintMode = false;
                window.setMouseCursorVisible(true);
            }
            updateMenu(window);
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

    colorPreview.setPosition(1520 + 30, 960);
    
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
    scene->changed = true;
}

void Menu::rotate(Vec3d& v) { /// would be added more functionality
    for (Object& o : scene->objects)
        if (o.isSelected)
            o.rotate(v);
    scene->updateView();
    scene->changed = true;
}

void Menu::scale(Vec3d& v) { /// would be added more functionality
    for (Object& o : scene->objects)
        if (o.isSelected)
            o.scale(v);
    scene->updateView();
    scene->changed = true;
}

void Menu::handleEvent(sf::RenderWindow& window, sf::Event event) {
    bool hasToUpdateMenu = false;
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    if (posX <= mouseX && mouseX <= posX + viewWidth && posY <= mouseY && mouseY <= posY + viewHeight)
        for (Button& b : objectsListItems)
            b.handleEvent(window, event, { posX, posY - viewOffset });

    for (Button& b : menuButtons) b.handleEvent(window, event);

    if (scene->editMode)
        for (InputBox& i : vertexProprieties) { if (i.handleEvent(window, event)) hasToUpdateMenu = true; }
    else
        for (InputBox& i : objectProprieties) if (i.handleEvent(window, event)) hasToUpdateMenu = true;

    if (scene->paintMode) {
        redSlider.handleEvent(window, event, paintColor);
        greenSlider.handleEvent(window, event, paintColor);
        blueSlider.handleEvent(window, event, paintColor);

        for (Button& b : menuColors) b.handleEvent(window, event);
    }

    switch (event.type) {
    case sf::Event::MouseWheelScrolled:
        if (posX <= mouseX && mouseX <= posX + viewWidth && posY <= mouseY && mouseY <= posY + viewHeight) {
            viewOffset -= event.mouseWheelScroll.delta * scrollSpeed;
            viewOffset = std::max(0.0f, std::min(viewOffset, objectsListHeight)); ///makes sure 0 <= viewOffset <= objectsListHeight
            hasToUpdateMenu = true;
        }
        break;
    }
    if (hasToUpdateMenu) updateMenu(window);
}

void Menu::updateMenu(sf::RenderWindow& window) {
    objectsListItems.clear();

    int objectPropretiesTotalCount = 0;
    float topLimit = viewOffset - boxHeight;
    float bottomLimit = viewOffset + viewHeight;


    for (int idx = 0; idx < scene->objects.size(); ++idx) {
        sf::Vector2f pos(2 * boxMargin, 2 * boxMargin + idx * (boxHeight + boxMargin) + objectPropretiesTotalCount * (boxHeight + boxMargin - 10));
        sf::Vector2f size(boxWidth, boxHeight);
        if (pos.y > bottomLimit) break;

        sf::Vector2f sizeBtn = { 45, boxHeight - 10 };
        sf::Vector2f posShow = { pos.x + size.x + 5, pos.y + 5 };
        sf::Vector2f posEdit = { pos.x + size.x + sizeBtn.x + 8, pos.y + 5 };
        sf::Vector2f posDelete = { pos.x + size.x + 2 * sizeBtn.x + 11, pos.y + 5 };

        std::string objectName = scene->objects[idx].name;
        if (objectName == "") objectName = "Object " + std::to_string(idx);

        if (pos.y > topLimit) {
            objectsListItems.emplace_back(objectName, size, pos, 21, ((scene->objects[idx].isSelected) ? ColorManager::tertiary : ColorManager::light), ColorManager::dark, [idx, &window, this]() {
                scene->objects[idx].isSelected = !scene->objects[idx].isSelected;
                updateMenu(window);
                });

            objectsListItems.emplace_back("show", sizeBtn, posShow, 18, ColorManager::light, ColorManager::dark, [idx, &window, this]() {
                scene->objects[idx].showObjectProprieties = !scene->objects[idx].showObjectProprieties;
                updateMenu(window);
                });

            objectsListItems.emplace_back("edit", sizeBtn, posEdit, 18, ColorManager::light, ColorManager::dark, [idx, &window, this]() {
                std::string newObjectName = scene->objects[idx].name;
                if (Modal::getNameDialog(window, "Enter new name:", newObjectName)) {
                    scene->objects[idx].name = newObjectName;
                    updateMenu(window);
                }
                });
            objectsListItems.emplace_back("del", sizeBtn, posDelete, 18, ColorManager::light, ColorManager::dark, [idx, &window, this]() {
                if (Modal::getOkDialog(window, "Are you sure you want to delete " + scene->objects[idx].name + "?")) {
                    scene->deleteObject(idx);
                    updateMenu(window);
                }
                });
        }


        if (scene->objects[idx].showObjectProprieties) {
            if (scene->editMode) {
                int count = 0;
                sf::Vector2f sizeBtn1 = { 90, boxHeight - 10 };
                sf::Vector2f sizeBtn2 = { 70, boxHeight - 10 };
                for (int v_idx = 0; v_idx < scene->objects[idx].vertices.size();v_idx++) {
                    sf::Vector2f posV = { pos.x + 8, pos.y + boxHeight + boxMargin + (boxHeight - 10 + boxMargin) * count };
                    if (posV.y > bottomLimit) break;
                    bool selected = scene->objects[idx].vertices[v_idx].isSelected;
                    if (posV.y > topLimit)
                        objectsListItems.emplace_back("vertex " + std::to_string(v_idx), sizeBtn1, posV, 18, (selected ? ColorManager::tertiary : ColorManager::light), ColorManager::dark, [idx, v_idx, &window, this]() {
                        scene->objects[idx].vertices[v_idx].isSelected = !scene->objects[idx].vertices[v_idx].isSelected;
                        updateMenu(window);
                            });
                    count++;
                    auto getStr = [](float value) {
                        return (value < 0 ? "- " : "  ") + std::to_string(+abs((int)value)) + "." + std::to_string(abs(((int)(value * 100) % 100)));
                        };

                    if (scene->objects[idx].vertices[v_idx].isSelected) {
                        sf::Vector2f pos1 = { pos.x + 15, pos.y + (boxHeight - 10 + boxMargin) * count + boxHeight + boxMargin };
                        sf::Vector2f pos2 = { pos.x + sizeBtn2.x + 18, pos.y + (boxHeight - 10 + boxMargin) * count + boxHeight + boxMargin };
                        sf::Vector2f pos3 = { pos.x + 2 * sizeBtn2.x + 21, pos.y + (boxHeight - 10 + boxMargin) * count + boxHeight + boxMargin };

                        if (posV.y > topLimit) {
                            objectsListItems.emplace_back(getStr(scene->objects[idx].vertices[v_idx].v.x), sizeBtn2, pos1, 18, ColorManager::light, ColorManager::dark);
                            objectsListItems.emplace_back(getStr(scene->objects[idx].vertices[v_idx].v.y), sizeBtn2, pos2, 18, ColorManager::light, ColorManager::dark);
                            objectsListItems.emplace_back(getStr(scene->objects[idx].vertices[v_idx].v.z), sizeBtn2, pos3, 18, ColorManager::light, ColorManager::dark);
                        }
                        count++;
                    }
                }
                objectPropretiesTotalCount += count;
            }
            else {
                int count = 0;
                sf::Vector2f sizeBtn1 = { 110, boxHeight - 10 };
                for (int t_idx = 0; t_idx < scene->objects[idx].triangles.size();t_idx++) {
                    sf::Vector2f posV = { pos.x + 8, pos.y + boxHeight + boxMargin + (boxHeight - 10 + boxMargin) * count };
                    if (posV.y > bottomLimit) break;
                    bool selected = scene->objects[idx].triangles[t_idx].isSelected;
                    if (posV.y > topLimit)
                        objectsListItems.emplace_back("triangle " + std::to_string(t_idx), sizeBtn1, posV, 18, (selected ? ColorManager::tertiary : ColorManager::light), ColorManager::dark, [idx, t_idx, &window, this]() {
                        scene->objects[idx].triangles[t_idx].isSelected = !scene->objects[idx].triangles[t_idx].isSelected;
                        updateMenu(window);
                            });
                    count++;
                }
                objectPropretiesTotalCount += count;
            }
        }

    }
    objectsListHeight = std::max(viewHeight, 2 * boxMargin + scene->objects.size() * (boxHeight + boxMargin) + objectPropretiesTotalCount * (boxHeight + boxMargin - 10));
}


void Menu::drawTo(sf::RenderWindow& window) {
    if (scene->changed) {
        scene->changed = false;
        updateMenu(window);
    }
    
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

        txt.setString("RGB Sliders");
        txt.setPosition({ 1520 + 30, 700 });
        window.draw(txt);

        txt.setString("Color Preview");
        txt.setPosition({ 1520 + 30, 935 });
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

        redSlider.updateColor(paintColor.r);
        greenSlider.updateColor(paintColor.g);
        blueSlider.updateColor(paintColor.b);

        colorPreview.setFillColor(paintColor);

        redSlider.drawTo(window);
        greenSlider.drawTo(window);
        blueSlider.drawTo(window);
        window.draw(colorPreview);
    }
}


