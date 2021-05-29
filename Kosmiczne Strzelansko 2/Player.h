#pragma once

#include "Entity.h"

class Player : public Entity {
	int lives;
	int score;
	int laserPower;
	float shakingSpeed;
	bool laserShot;
	std::vector <Entity> playerLasers;
	// tekstura lasera
	Texture laserTexture;
public:
	Player();
	void setLaserTexture(Texture newLaserTexture);
	Sprite getLaserSprite(int number);
	void shootLaser();
	void stopLaser();
	bool getLaserState();
	void generateLaserInstance();
	int getLaserCount();
	FloatRect getLaserBounds(int number);
	void shakeShip();
	void update(float deltaTime, bool shaking);
};