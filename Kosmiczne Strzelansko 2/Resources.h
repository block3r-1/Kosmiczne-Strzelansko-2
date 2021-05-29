#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Resources {
	Texture playerTexture;
	Texture backgroundTexture;
	Texture laserTexture;
	Texture asteroidTexture;
public:
	void loadPlayerTexture(std::string textureName);
	void loadBackgroundTexture(std::string textureName);
	void loadLaserTexture(std::string textureName);
	void loadAsteroidTexture(std::string textureName);
	Texture getPlayerTexture();
	Texture getBackgroundTexture();
	Texture getLaserTexture();
	Texture getAsteroidTexture();
};