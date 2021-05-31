#include <random>
#include <iostream>

#include "Alien.h"

#define LASER_TIME 0.5
#define ACTION_TIME 0.5
#define FOLLOW_INTERVAL 0.1

#define AI_CHANCE0 50
#define AI_CHANCE1 25
#define AI_CHANCE2 75

Alien::Alien() {
	std::random_device seed;
	std::default_random_engine generator(seed());

	std::uniform_int_distribution <int> behaviour(0, 100);
	int typeToAssign = behaviour(seed);
	if (typeToAssign > 0 && typeToAssign < 33) AItype = 0; // normal
	else if (typeToAssign > 33 && typeToAssign < 66) AItype = 1; // mild;
	else if (typeToAssign > 66 && typeToAssign < 100) AItype = 2; // furious
	else AItype = 0;

	isFollowing = false;
	sideMovement = false;
	hideNSeek = false;
	mildShooting = false;
	furiousShooting = false;
	replyShooting = false;

	switch (AItype) {
	case 0: // normal
		speed = 700;
		laserSpeed = 700;
		break;
	case 1: // mild
		speed = 450;
		laserSpeed = 500;
		break;
	case 2: // furious
		speed = 800;
		laserSpeed = 1200;
		break;
	}
	//speed = 500;
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

void Alien::makeAction(float deltaTime, int xPlayer) {
	std::random_device seed;
	std::default_random_engine generator(seed());

	static float followTimer = 0; // dlugosc aktualnego sledzenia (jak dotad)
	static float followDuration = 0; // dlugosc aktualnego sledzenia (przy ktorej sledzenie sie zakonczy)
	static float followInterval = 0; // licznik odliczajacy czas pomiedzy kolejnymi sledzeniami

	// STRZELANIE LASERAMI
	std::uniform_int_distribution <int> laserChance(0, 100);
	int laserPercentage = laserChance(seed);
	switch (AItype) {
	case 0: // normal
		if (laserPercentage < AI_CHANCE0) this->shootLaser();
		else this->stopLaser();
		break;
	case 1: // mild
		if (laserPercentage < AI_CHANCE1) this->shootLaser();
		else this->stopLaser();
		break;
	case 2: // furious
		if (laserPercentage < AI_CHANCE2) this->shootLaser();
		else this->stopLaser();
		break;
	}

	// SLEDZENIE GRACZA
	if (followInterval > FOLLOW_INTERVAL) {
		if (isFollowing == false) {
			std::uniform_int_distribution <int> followChance(0, 100);
			int followPercentage = followChance(seed);

			std::uniform_int_distribution <int> followTime(0, 10);
			followDuration = 0.1;//followTime(seed) / 100;

			switch (AItype) {
			case 0: // normal - 30%
				if (followPercentage < (AI_CHANCE0 - 20)) isFollowing = true;
				break;
			case 1: // mild - 15%
				if (followPercentage < (AI_CHANCE1 - 10)) isFollowing = true;
				break;
			case 2: // furious - 45% szans
				if (followPercentage < (AI_CHANCE2 - 30)) isFollowing = true;
				break;
			}
		}
	}
	if(isFollowing == true) {
		followInterval = 0;
		this->follow(xPlayer);
		std::cout << "FOLLOWING" << std::endl;
		if (followTimer > followDuration) {
			isFollowing = false;
			followTimer = 0;
			followInterval = 0;
		}
		followTimer += deltaTime;
	}
	followInterval += deltaTime;
	std::cout << "FOLLOW INTERVAL: " << followInterval << std::endl;
}

void Alien::updateAI(float deltaTime, int xPlayer, bool shaking) {


	static float AIcounter = 0;

	static bool sideMovementDir = false;
	static float laserTimer = 0;
	if (runawayEnded == false) {
		if (position.x < -50 || position.x > (VideoMode::getDesktopMode().width + 50)) {
			this->leftStop();
			this->rightStop();
			runawayEnded = true;
		}
	}
	if (AIcounter > ACTION_TIME) {
		this->makeAction(deltaTime, xPlayer);
		AIcounter = 0;
	}
	if (isFollowing == false) {
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
	}
		if (laserShot == true) {
			if (laserTimer > LASER_TIME) {
				this->generateLaserInstance(laserSpeed);
				laserTimer = 0;
			}
		}
	laserTimer += deltaTime;

	this->updateLasers(deltaTime);
	this->update(deltaTime, shaking);
	AIcounter += deltaTime;
}