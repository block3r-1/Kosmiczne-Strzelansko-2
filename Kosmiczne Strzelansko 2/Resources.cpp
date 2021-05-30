#include <SFML/Graphics.hpp>

#include "Resources.h"

using namespace sf;

void Resources::loadPlayerTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	playerTexture.loadFromFile(texturePath);
	playerTexture.loadFromFile(textureName);

}

void Resources::loadSecondPlayerTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	secondPlayerTexture.loadFromFile(texturePath);
	secondPlayerTexture.loadFromFile(textureName);
}

void Resources::loadAlienTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	alienTexture.loadFromFile(texturePath);
	alienTexture.loadFromFile(textureName);
}

void Resources::loadBackgroundTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	backgroundTexture.loadFromFile(texturePath);
	backgroundTexture.loadFromFile(textureName);
}

void Resources::loadLaserTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	laserTexture.loadFromFile(texturePath);
	laserTexture.loadFromFile(textureName);
}

void Resources::loadAsteroidTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	asteroidTexture.loadFromFile(texturePath);
	asteroidTexture.loadFromFile(textureName);
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