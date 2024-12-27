#include "FontManager.hpp"

FontManager* FontManager::instancePtr = nullptr;

FontManager::FontManager() {
	this->loadFromFile("../../../assets/Roboto-Regular.ttf");
}

FontManager* FontManager::getInstance() {
	if (instancePtr == nullptr) {
		instancePtr = new FontManager();
	}
	return instancePtr;
}