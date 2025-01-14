#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include "../feature/Scene.hpp"
#include "../../src/managers/FontManager.hpp"
#include "../../src/managers/ColorManager.hpp"
#include "../../src/ui/Button.hpp"
#include "../../src/ui/InputBox.hpp"
#include "../../src/ui/Slider.hpp"
#include "../../src/ui/CustomCursor.hpp"
#include "../../src/views/Home.hpp"


class Menu {
	
	Scene *scene;
	Home *home;
	float scrollSpeed = 20.0f;
	const float viewWidth = 350;
	const float viewHeight = 400;
	const float boxWidth = 175;
	const float boxHeight = 35;
	const float boxMargin = 7;
	float viewOffset = 0;
	float objectsListHeight;
	float posX, posY;
	float width, height, offsetLeft;
	sf::RectangleShape menuBackground, viewBackground;
	std::vector<bool> showTriangles, showVertices, showObjectProps;
	std::vector<Button> objectsListItems, menuButtons, menuColors;
	std::vector<InputBox> objectProprieties, vertexProprieties;
	sf::Color paintColor;
	Slider redSlider, greenSlider, blueSlider;
	sf::RectangleShape colorPreview;
	CustomCursor bucketCursor;

public:
	
	Menu(sf::RenderWindow &, float, float, float);
	void translate(Vec3d&);
	void rotate(Vec3d&);
	void scale(Vec3d&);
	void updateMenu(sf::RenderWindow&);
	void handleEvent(sf::RenderWindow &, sf::Event);
	void drawTo(sf::RenderWindow &);
};

#endif