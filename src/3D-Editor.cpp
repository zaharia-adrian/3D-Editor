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

const float HEIGHT = 1080; ///window width
const float WIDTH = 1920; ///window height
const float SCENE_WIDTH = 1470;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D-Editor");
    
    Scene *scene = Scene::getInstance();
    scene->loadFromFile("../../../localProjects/Spaceship.txt");
    

    sf::Color Gray(128, 128, 128);
    Button btn1("Edit Mode", { 150, 40 }, 20, Gray, sf::Color::Black);
    btn1.setPosition({ 1295, 25 });

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
            btn1.handleEvent(window, event);
            menu.handleEvent(event);
        }
        
        window.clear(sf::Color(26,26,26));
       
        scene->drawTo(window);
        btn1.drawTo(window);
        menu.drawTo(window);
 
        window.display();
    }

    return 0;
}