#pragma once

#include "Entity.h"

class Player : public Entity {
	int lives;
	int score;
	int laserPower;
	float shakingSpeed;
	std::vector <Entity> playerLasers;
public:
	Player();
	void shootLaser();
	void shakeShip();
	void update(float deltaTime, bool shaking);
};