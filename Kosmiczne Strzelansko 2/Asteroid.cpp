#include <cmath>
#include <random>

#include "Asteroid.h"

Asteroid::Asteroid() {
	std::random_device seed;
	std::default_random_engine generator(seed());

	std::uniform_int_distribution <int> speedDistribution(0, 100);
	std::uniform_int_distribution <int> rotationSpeedDistribution(0, 50);

	speed = speedDistribution(seed);
	rotationSpeed = rotationSpeedDistribution(seed);

	size = 3;
	hitCount = 0;

	std::uniform_int_distribution <int> xDistribution(0, VideoMode::getDesktopMode().width);
	std::uniform_int_distribution <int> yDistribution(0, VideoMode::getDesktopMode().height);
	this->setPosition(xDistribution(seed), yDistribution(seed));

	std::uniform_int_distribution <int> angleDistribution(0, 360);
	angle = angleDistribution(seed);

	outOfBounds = false;
}

Asteroid::Asteroid(int level) {
	std::random_device seed;
	std::default_random_engine generator(seed());

	std::uniform_int_distribution <int> speedDistribution(50, 300);
	std::uniform_int_distribution <int> rotationSpeedDistribution(0, 50);

	speed = speedDistribution(seed);
	rotationSpeed = rotationSpeedDistribution(seed);

	size = level;
	hitCount = 0;

	std::uniform_int_distribution <int> angleDistribution(0, 360);
	angle = angleDistribution(seed);

	outOfBounds = false;
}

void Asteroid::hit() {

	std::random_device seed;
	std::default_random_engine generator(seed());
	//std::uniform_int_distribution <int> angleDistribution((angle - 60), (angle + 60));
	angle = -angle;//angleDistribution(seed);

	//this->update(0.007);
	hitCount++;

	if (hitCount > 1000) {
		this->setPosition(-500, -500);
		hitCount = 0;
	}

	position.x = position.x + speed * 0.004 * cos(angle * 3.14159 / 180);
	position.y = position.y + speed * 0.004 * sin(angle * 3.14159 / 180);
	this->setPosition(position.x, position.y);
}

void Asteroid::respawn() {
	std::random_device seed;
	std::default_random_engine generator(seed());

	float xPos, yPos;

	std::uniform_int_distribution <int> leftOrRight(0, 100);
	std::uniform_int_distribution <int> xOrY(0, 100);

	if (xOrY(seed) > 60) {
		std::uniform_int_distribution <int> xDistribution(0, VideoMode::getDesktopMode().width + 20);
		xPos = xDistribution(seed);
		yPos = -20;
	}
	else {
		std::uniform_int_distribution <int> yDistribution(0, VideoMode::getDesktopMode().height + 20);
		yPos = yDistribution(seed);

		if (leftOrRight(seed) > 30) {
			xPos = -30;
			std::uniform_int_distribution <int> angleDistribution(0, 360);
			angle = angleDistribution(seed);
		}
		else {
			xPos = VideoMode::getDesktopMode().width + 30;
			std::uniform_int_distribution <int> angleDistribution(90, 270);
			angle = angleDistribution(seed);
		}
	}

	this->setPosition(xPos, yPos);

	outOfBounds = false;
}

void Asteroid::update(float deltaTime) {
	float distance = speed * deltaTime;
	position.x = position.x + distance * cos(angle * 3.14159 / 180);
	position.y = position.y + distance * sin(angle * 3.14159 / 180);
	this->setPosition(position.x, position.y);

	float angularDistance = rotationSpeed * deltaTime;
	sprite.rotate(angularDistance);

	if (position.x < -50 || position.x > (VideoMode::getDesktopMode().width + 50) ||
		position.y < -50 || (position.y > VideoMode::getDesktopMode().height + 50)) {
		outOfBounds = true;
	}
	else {
		outOfBounds = false;
	}

	if (outOfBounds == true) this->respawn();
}