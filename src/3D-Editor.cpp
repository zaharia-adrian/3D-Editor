#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../src/utils/Mat4x4.hpp"
#include "../src/utils/Vec3d.hpp"
#include "../src/feature/Button.hpp"
#include "../src/feature/Scene.hpp"
#include "../src/views/Menu.hpp"
#include "../src/managers/FontManager.hpp"
#include <filesystem>

const float HEIGHT = 1080; ///window height
const float WIDTH = 1920; ///window width
const float SCENE_WIDTH = 1470;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D-Editor");

    Scene* scene = Scene::getInstance();
    scene->loadFromFile("../../../localProjects/Cube.txt");

    Menu menu(WIDTH - SCENE_WIDTH, HEIGHT, SCENE_WIDTH);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            scene->handleEvent(event);
            menu.handleEvent(window, event);
        }

        window.clear(sf::Color(26, 26, 26));

        scene->drawTo(window);
        menu.drawTo(window);

        window.display();
    }

    return 0;
}