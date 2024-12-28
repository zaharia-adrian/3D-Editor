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
const float SCENE_WIDTH = 1470;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D-Editor");

    Menu menu(WIDTH - SCENE_WIDTH, HEIGHT, SCENE_WIDTH);

    Home *home = Home::getInstance();
    Scene *scene = Scene::getInstance();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if (home->homePageView) {
                home->handleEvent(window, event);
            }else {
                scene->handleEvent(window, event);
                menu.handleEvent(window, event);
            }
        }

        window.clear(ColorManager::dark);

        if (home->homePageView) {
            home->drawTo(window);
        }else {
            scene->drawTo(window);
            menu.drawTo(window);
        }   
        window.display();
    }

    return 0;
}