#include <cmath>
#include <random>

#include "Asteroid.h"

Asteroid::Asteroid() {
	speed = 100;
	size = 3;

	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_int_distribution <int> xDistribution(0, VideoMode::getDesktopMode().width);
	std::uniform_int_distribution <int> yDistribution(0, VideoMode::getDesktopMode().height);
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

void Asteroid::hit() {
	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_int_distribution <int> angleDistribution(0, 360);
	angle = angleDistribution(seed);
	this->update(0.01);
}

void Asteroid::update(float deltaTime) {
	float distance = speed * deltaTime;
	position.x = position.x + distance * cos(angle * 3.14159 / 180);
	position.y = position.y + distance * sin(angle * 3.14159 / 180);
	this->setPosition(position.x, position.y);
}