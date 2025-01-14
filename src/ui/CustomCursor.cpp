#include "CustomCursor.hpp"

Scene* scene = Scene::getInstance();

CustomCursor::CustomCursor(std::string imagePath) {
	if (!cursorImage.loadFromFile(imagePath.c_str())) {
		std::cerr << "Failed to load cursor image!" << std::endl;
	}
    for (int x = 0; x < cursorImage.getSize().x; x++) {
        for (int y = 0; y < cursorImage.getSize().y; y++) {
            sf::Color pixelColor = cursorImage.getPixel(x, y);

            // Lighten black pixels to make them tintable
            
            if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0 && pixelColor.a != 0) {
                pixelColor.r = 128;
                pixelColor.g = 128;
                pixelColor.b = 128;
            }

            cursorImage.setPixel(x, y, pixelColor);
        }
    }
    if (!cursorTexture.loadFromImage(cursorImage)) {
        std::cerr << "Failed to load cursor texture!" << std::endl;
    }
    cursorSprite.setTexture(cursorTexture);
    cursorSprite.setScale(0.085f, 0.085f);
    cursorSprite.setOrigin(cursorTexture.getSize().x / 2, cursorTexture.getSize().y / 2);
}

void CustomCursor::update(sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    cursorSprite.setPosition(mousePosition.x, mousePosition.y);
    cursorSprite.setColor(scene->menuPaintColor);
}

void CustomCursor::drawTo(sf::RenderWindow& window) {
   if (scene->paintMode) {
        window.draw(cursorSprite);
        window.setMouseCursorVisible(false);
   }
}