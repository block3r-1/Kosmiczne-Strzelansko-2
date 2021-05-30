#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Resources {
	Texture playerTexture;
	Texture secondPlayerTexture;
	Texture alienTexture;
	Texture backgroundTexture;
	Texture laserTexture;
	Texture asteroidTexture;
public:
	void loadPlayerTexture(std::string textureName);
	void loadSecondPlayerTexture(std::string textureName);
	void loadAlienTexture(std::string textureName);
	void loadSecondAlienTexture(std::string textureName);
	void loadBackgroundTexture(std::string textureName);
	void loadLaserTexture(std::string textureName);
	void loadAsteroidTexture(std::string textureName);
	Texture getPlayerTexture();
	Texture getSecondPlayerTexture();
	Texture getAlienTexture();
	Texture getSecondAlienTexture();
	Texture getBackgroundTexture();
	Texture getLaserTexture();
	Texture getAsteroidTexture();
};