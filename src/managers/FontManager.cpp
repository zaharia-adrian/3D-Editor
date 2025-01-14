#include "FontManager.hpp"

FontManager* FontManager::instancePtr = nullptr;

FontManager::FontManager() {
	this->loadFromFile("../../../assets/fonts/Roboto-Regular.ttf");
}

FontManager* FontManager::getInstance() {
	if (instancePtr == nullptr) {
		instancePtr = new FontManager();
	}
	return instancePtr;
}