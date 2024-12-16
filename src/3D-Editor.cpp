#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../src/utils/Mat4x4.hpp"
#include "../src/utils/Vec3d.hpp"
#include "../src/feature/Button.hpp"
#include "../src/feature/Scene.hpp"
#include "../src/views/Menu.hpp"
#include <filesystem>

const float HEIGHT = 1080; ///window width
const float WIDTH = 1920; ///window height
const float SCENE_WIDTH = 1470;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D-Editor");
    
    Scene S(SCENE_WIDTH, HEIGHT);
    S.loadFromFile("../../../localProjects/Cube.txt");
    
    sf::Font arial;
    arial.loadFromFile("../../../assets/arial.ttf");

    
    sf::Color Gray(128, 128, 128);
    Button btn1("Switch visibility", { 200, 50 }, 20, Gray, sf::Color::Black);
    btn1.setFont(arial);
    btn1.setPosition({ 100, 300 });

    Menu menu(WIDTH - SCENE_WIDTH,HEIGHT, SCENE_WIDTH);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape
                )
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                if (btn1.isMouseOver(window)) {
                    if (!btn1.isPressed()) {
                        btn1.setBackColor(sf::Color::Blue);
                    }
                } else {
                    btn1.setBackColor(Gray);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (btn1.isMouseOver(window)) {
                    btn1.setBackColor(sf::Color::Green);
                    btn1.press();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                btn1.release();
                if (btn1.isMouseOver(window)) {
                    btn1.switchOnOff();
                    btn1.setBackColor(sf::Color::Blue);
                }
            }
           
            S.handleMoveCamera(event);
 
        }
        
        window.clear(sf::Color::Black);

        if (!btn1.isSwitchedOn()) {
            S.drawTo(window);
        }
     

        btn1.drawTo(window);
        menu.drawTo(window);
 
        window.display();
       
    }
    return 0;
}

