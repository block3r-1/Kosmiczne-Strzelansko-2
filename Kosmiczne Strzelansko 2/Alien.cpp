#include <random>

#include "Alien.h"

#define LASER_TIME 0.5

Alien::Alien() {
	std::random_device seed;
	std::default_random_engine generator(seed());

	std::uniform_int_distribution <int> behaviour(0, 2);
	AItype = behaviour(seed);

	isFollowing = false;
	sideMovement = false;
	hideNSeek = false;
	mildShooting = false;
	furiousShooting = false;
	replyShooting = false;

	speed = 500;
	shakingSpeed = 50;
	lives = 0;
	score = 0;

	laserShot = false;
	l = false;
	r = false;
	u = false;
	d = false;
}

void Alien::follow(int xPlayer) {
	if (xPlayer > position.x) this->right();
	else this->rightStop();

	if (xPlayer < position.x) this->left();
	else this->leftStop();
}

void Alien::runAway() {
	std::random_device seed;
	std::default_random_engine generator(seed());

	std::uniform_int_distribution <int> direction(0, 1);
		if (direction(seed) == 0) {
			this->right();
			runawayEnded = false;
		}
		else {
			this->left();
			runawayEnded = false;
		}
}

void Alien::sideToSide(int direction) {

}

void Alien::updateLasers(float deltaTime) {
	if (playerLasers.empty() == true) return;

	auto laserIterator = playerLasers.begin();
	while (laserIterator != playerLasers.end()) {
		laserIterator->setTexture(laserTexture);
		laserIterator->down();
		laserIterator->update(deltaTime);
		if (laserIterator->getPosition().y > VideoMode::getDesktopMode().height) {
			laserIterator = playerLasers.erase(laserIterator);
		}
		else {
			laserIterator++;
		}
	}
}

void Alien::updateAI(float deltaTime, int xPlayer, bool shaking) {
	static bool sideMovementDir = false;
	static float laserTimer = 0;
	if (runawayEnded == false) {
		if (position.x < -50 || position.x > (VideoMode::getDesktopMode().width + 50)) {
			this->leftStop();
			this->rightStop();
			runawayEnded = true;
		}
	}
	//if (laserTimer > deltaTime) {
		this->shootLaser();
	//	laserTimer = 0;
	//}
	//else {
	//	this->stopLaser();
	//}
	sideMovement = true;
	if (sideMovement == true) {
		if (sideMovementDir == true) { // w lewo
			this->left();
			this->rightStop();
		}
		else { // w prawo
			this->right();
			this->leftStop();
		}
		if (position.x < 200) sideMovementDir = false;
		if (position.x > (VideoMode::getDesktopMode().width - 200)) sideMovementDir = true;
	}

	if (laserShot == true) {
		if (laserTimer > LASER_TIME) {
			this->generateLaserInstance();
			laserTimer = 0;
		}
	}
	laserTimer += deltaTime;

	this->updateLasers(deltaTime);
	this->update(deltaTime, shaking);
}