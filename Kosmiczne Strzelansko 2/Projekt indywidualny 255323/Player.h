#pragma once

#include "Entity.h"

class Player : public Entity {
protected:
	int lives;
	int score;

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
	void generateLaserInstance(int laserSpeed);
	int getLaserCount();
	FloatRect getLaserBounds(int number);
	void shakeShip();
	void decreaseLives();
	void increaseScore();
	int getScore();
	int getLives();
	void updateLasers(float deltaTime);
	void update(float deltaTime, bool shaking);
};