#include <SFML/Graphics.hpp>

#include "Resources.h"

using namespace sf;

void Resources::loadPlayerTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	playerTexture.loadFromFile(texturePath);

}

void Resources::loadSecondPlayerTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	secondPlayerTexture.loadFromFile(texturePath);
}

void Resources::loadAlienTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	alienTexture.loadFromFile(texturePath);
}

void Resources::loadBackgroundTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	backgroundTexture.loadFromFile(texturePath);
}

void Resources::loadLaserTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	laserTexture.loadFromFile(texturePath);
}

void Resources::loadAsteroidTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	asteroidTexture.loadFromFile(texturePath);
}

void Resources::loadFont(std::string fontName) {
	std::string fontPath = "fonts\\" + fontName + ".ttf";
	textFont.loadFromFile(fontPath);
}

Texture Resources::getPlayerTexture() {
	return playerTexture;
}

Texture Resources::getSecondPlayerTexture() {
	return secondPlayerTexture;
}

Texture Resources::getAlienTexture() {
	return alienTexture;
}

Texture Resources::getBackgroundTexture() {
	return backgroundTexture;
}

Texture Resources::getLaserTexture() {
	return laserTexture;
}

Texture Resources::getAsteroidTexture() {
	return asteroidTexture;
}

Font Resources::getTextFont() {
	return textFont;
}