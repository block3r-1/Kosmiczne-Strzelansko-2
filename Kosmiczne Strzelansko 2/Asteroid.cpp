#include <cmath>
#include <random>

#include "Asteroid.h"

Asteroid::Asteroid() {
	speed = 100;
	size = 3;

	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_int_distribution <int> xDistribution(400, 1500);
	std::uniform_int_distribution <int> yDistribution(300, 800);
	this->setPosition(xDistribution(seed), yDistribution(seed));

	std::uniform_int_distribution <int> angleDistribution(0, 360);
	angle = angleDistribution(seed);
}

Asteroid::Asteroid(int level) {
	speed = 100;
	angle = 50;
	size = level;
	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_int_distribution <int> angleDistribution(0, 360);
	angle = angleDistribution(seed);
}

void Asteroid::update(float deltaTime) {
	float distance = speed * deltaTime;
	position.x = position.x + distance * cos(angle * 3.14159 / 180);
	position.y = position.y + distance * sin(angle * 3.14159 / 180);
	this->setPosition(position.x, position.y);
}