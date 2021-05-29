#pragma once

#include "Entity.h"

class Asteroid : public Entity {
	float rotationSpeed;
	int size;
	float angle;
	//Vector2 <float> movementDirection;
public:
	Asteroid();
	Asteroid(int level);
	void update(float deltaTime);
};