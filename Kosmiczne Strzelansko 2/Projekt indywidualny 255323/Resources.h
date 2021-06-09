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
	Font textFont;

public:
	void loadPlayerTexture(std::string textureName);
	void loadSecondPlayerTexture(std::string textureName);
	void loadAlienTexture(std::string textureName);
	void loadBackgroundTexture(std::string textureName);
	void loadLaserTexture(std::string textureName);
	void loadAsteroidTexture(std::string textureName);
	void loadFont(std::string fontName);

	Texture getPlayerTexture();
	Texture getSecondPlayerTexture();
	Texture getAlienTexture();
	Texture getBackgroundTexture();
	Texture getLaserTexture();
	Texture getAsteroidTexture();
	Font getTextFont();
};