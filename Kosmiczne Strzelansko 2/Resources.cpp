#include <SFML/Graphics.hpp>

#include "Resources.h"

using namespace sf;

void Resources::loadPlayerTexture(std::string textureName) {
	std::string texturePath = "textures\\" + textureName + ".png";
	playerTexture.loadFromFile(texturePath);
	playerTexture.loadFromFile(textureName);

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
Texture Resources::getPlayerTexture() {
	return playerTexture;
}
Texture Resources::getBackgroundTexture() {
	return backgroundTexture;
}
Texture Resources::getLaserTexture() {
	return laserTexture;
}