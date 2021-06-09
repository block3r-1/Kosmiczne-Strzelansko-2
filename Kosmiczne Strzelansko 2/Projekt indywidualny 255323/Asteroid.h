#pragma once

#include "Entity.h"

class Asteroid : public Entity {
	float rotationSpeed;
	float angle;
	//int hitCount;
	
	bool outOfBounds;
public:
	Asteroid();
	Asteroid(int level);
	void hit();
	void respawn();
	void update(float deltaTime);
};