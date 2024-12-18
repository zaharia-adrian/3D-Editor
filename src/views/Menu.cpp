#include "Menu.hpp"

Menu::Menu(float width, float height, float offsetLeft) :
    width(width),
    height(height),
    offsetLeft(offsetLeft),
    posX(offsetLeft + (width - viewWidth) / 2.0f),
    posY((width - viewWidth) / 2.0f)
{
    scene = Scene::getInstance();


    showObjectProps = showTriangles = showVertices = std::vector<bool>(scene->objects.size(), false);

    ///menu background
    menuBackground = sf::RectangleShape({ width, height });
    menuBackground.setPosition({ offsetLeft, 0.0f });
	menuBackground.setFillColor(sf::Color(128, 128, 128));

    ///view backgound
    viewBackground = sf::RectangleShape({ viewWidth, viewHeight });
    viewBackground.setPosition({ posX, posY });
    viewBackground.setFillColor(sf::Color(100, 100, 100));

};

void Menu::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        viewOffset -= event.mouseWheelScroll.delta * scrollSpeed;
        viewOffset = std::max(0.0f, std::min(viewOffset, objectsListHeight)); ///makes sure 0 <= viewOffset <= objectsListHeight
    }else if (event.type == sf::Event::MouseButtonPressed) {
        float mouseX = event.mouseButton.x;
        float mouseY = event.mouseButton.y;


    }
}

void Menu::drawTo(sf::RenderWindow& window) const {

    sf::RenderTexture renderTexture;
    renderTexture.create(viewWidth, viewHeight);
    renderTexture.clear(sf::Color::Transparent);
    

    sf::View scrollView(sf::FloatRect(0, viewOffset, viewWidth, viewHeight));
    
    renderTexture.setView(scrollView);

    sf::RectangleShape box({ boxWidth, boxHeight });
    box.setFillColor(sf::Color(200, 200, 200));

    sf::Text text;
    text.setFont(*FontManager::getInstance());
    text.setCharacterSize(21);
    text.setFillColor(sf::Color(26, 26, 26));

    int itemsCount = 0;
    for (size_t idx = 0; idx < scene->objects.size(); ++idx) {
        
        auto drawBoxAndText = [&](float addOffset, std::string textStr) {
            box.setPosition((2 + addOffset) * boxMargin, 2 * boxMargin + itemsCount * (boxHeight + boxMargin));
            renderTexture.draw(box);

            text.setString(textStr);
            text.setPosition((2 + addOffset) * boxMargin + 5 + addOffset, 2 * boxMargin + 5 + itemsCount * (boxHeight + boxMargin));
            renderTexture.draw(text);
            itemsCount++;
        };

        std::string objectName = scene->objects[idx].name;
        if (objectName == "") objectName = "Object " + std::to_string(idx);

        drawBoxAndText(0,objectName);
        
        if (showObjectProps[idx]) {
            drawBoxAndText(2, "Triangles");
            if (showTriangles[idx]) 
                for (int i = 0;i < scene->objects[idx].triangles.size();i++)
                    drawBoxAndText(4, "Triangle " + std::to_string(i));
        }
        if (showObjectProps[idx]) {
            drawBoxAndText(2, "Vertices");
            if (showTriangles[idx])
                for (int i = 0;i < scene->objects[idx].vertices.size();i++)
                    drawBoxAndText(4, "Vertex " + std::to_string(i));
        }

    }
    renderTexture.display();

    float posX = offsetLeft + (width - viewWidth) / 2.0f;
    float posY = (width - viewWidth) / 2.0f;

    sf::Sprite clippedSprite(renderTexture.getTexture());
    clippedSprite.setPosition(posX, posY);

    window.draw(menuBackground);
    window.draw(viewBackground);    
    window.draw(clippedSprite);
}