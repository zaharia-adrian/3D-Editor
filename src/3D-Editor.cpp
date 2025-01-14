#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>


#include "../src/feature/Scene.hpp"
#include "../src/views/Menu.hpp"
#include "../src/views/Home.hpp"
#include "../src/managers/ColorManager.hpp"

const float HEIGHT = 1080; ///window height
const float WIDTH = 1920; ///window width
const float SCENE_WIDTH = 1520;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D-Editor");

    Menu menu(window, WIDTH - SCENE_WIDTH, HEIGHT, SCENE_WIDTH);

    Home *home = Home::getInstance(window);
    Scene *scene = Scene::getInstance();

    /// should put this somewhere else later
    sf::Image bucketImage;
    if (!bucketImage.loadFromFile("../../../assets/paint-bucket.png")) {
        std::cerr << "Failed to load image!" << std::endl;
    }
    for (int x = 0; x < bucketImage.getSize().x; x++) {
        for (int y = 0; y < bucketImage.getSize().y; y++) {
            sf::Color pixelColor = bucketImage.getPixel(x, y);

            // Lighten black pixels to make them tintable
            if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0 && pixelColor.a != 0) {
                pixelColor.r = 128;
                pixelColor.g = 128;
                pixelColor.b = 128;
            }

            bucketImage.setPixel(x, y, pixelColor);
        }
    }
    sf::Texture cursorTexture;
    if (!cursorTexture.loadFromImage(bucketImage)) {
        std::cerr << "Failed to load cursor image!" << std::endl;
    }
    sf::Sprite cursorSprite(cursorTexture);
    cursorSprite.setScale(0.085f, 0.085f);
    cursorSprite.setOrigin(cursorTexture.getSize().x / 2, cursorTexture.getSize().y / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                window.close();
                break;
            case sf::Event::Resized: {
                float width = static_cast<float>(window.getSize().x);
                float height = static_cast<float>(window.getSize().y);
                window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
                break;
            }
            default:
                break;
            }
            if (home->homePageView) {
                home->handleEvent(window, event);
            }else {
                scene->handleEvent(window, event);
                menu.handleEvent(window, event);
            }
        }
        /*
        // Update the color preview
        sf::Color currentColor(
            static_cast<sf::Uint8>(redSlider.getValue()),
            static_cast<sf::Uint8>(greenSlider.getValue()),
            static_cast<sf::Uint8>(blueSlider.getValue())
        );
        colorPreview.setFillColor(currentColor);
        */
        /// Update bucket position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        cursorSprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        cursorSprite.setColor(scene->menuPaintColor);

        window.clear(ColorManager::dark);
        if (home->homePageView) {
            home->drawTo(window);
        }else {
            scene->drawTo(window);
            menu.drawTo(window);
        }

        // Draw the sliders
        //redSlider.draw(window);
        //greenSlider.draw(window);
        //blueSlider.draw(window);
        //window.draw(colorPreview);

        /// Draw the bucket
        if (scene->paintMode) {
            window.draw(cursorSprite);
            window.setMouseCursorVisible(false);
        }

        window.display();
    }

    return 0;
}