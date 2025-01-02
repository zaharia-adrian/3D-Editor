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