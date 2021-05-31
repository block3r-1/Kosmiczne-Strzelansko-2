#include <random>
#include <iostream>

#include "Alien.h"

#define LASER_TIME 0.3
#define ACTION_TIME 1
#define HIDING_TIME 1
#define FOLLOW_INTERVAL 0.25
#define RUNAWAY_INTERVAL 0.4

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

void Alien::runAway(bool direction) {
		if (direction == true) {
			this->right();
			this->leftStop();
			runawayEnded = false;
		}
		else {
			this->left();
			this->rightStop();
			runawayEnded = false;
		}
}

void Alien::destroyLaser(int number) {
	playerLasers[number].setPosition(-500, (VideoMode::getDesktopMode().height + 500));
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

	static float runawayDuration = 0; // czas w jakim schowa sie za granica mapy
	static float runawayInterval = 0; // czas pomiedzy kolejnymi ucieczkami
	static bool runawayDir = false;

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

			//std::uniform_int_distribution <int> followTime(10, 20);
			followDuration = 0.1;//followTime(seed) / 100;

			switch (AItype) {
			case 0: // normal - 40%
				if (followPercentage < (AI_CHANCE0 - 10)) isFollowing = true;
				break;
			case 1: // mild - 25%
				if (followPercentage < AI_CHANCE1) isFollowing = true;
				break;
			case 2: // furious - 65% szans
				if (followPercentage < (AI_CHANCE2 - 10)) isFollowing = true;
				break;
			}
		}
	}
	if (isFollowing == true) {
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

	// UCIECZKA NA BOK
	if (runawayInterval > RUNAWAY_INTERVAL) {
		if (runawayEnded == true) {
			std::uniform_int_distribution <int> runawayChance(0, 100);
			int runawayPercentage = runawayChance(seed);

			std::uniform_int_distribution <int> runawayDirection(0, 1);
			runawayDir = runawayDirection(seed);

			if (runawayDirection(seed) == 0) runawayDir = true;
			else runawayDir = false;

			switch (AItype) {
			case 0: // normal - 50%
				if (runawayPercentage > AI_CHANCE0) runawayEnded = false;
				break;
			case 1: // mild - 75%
				if (runawayPercentage > AI_CHANCE1) runawayEnded = false;
				break;
			case 2: // furious - 25% szans
				if (runawayPercentage > AI_CHANCE2) runawayEnded = false;
				break;
			}
		}
	}
	if (runawayEnded == false) {
		runawayInterval = 0;
		this->runAway(runawayDir);
		std::cout << "RUNAWAY ";
		if (runawayDir == true) std::cout << "RIGHT" << std::endl;
		else std::cout << "LEFT" << std::endl;

		if (position.x == -10 || position.x == (VideoMode::getDesktopMode().width + 10)) runawayDuration = 0;

		if (position.x < -100 || position.x > (VideoMode::getDesktopMode().width + 100)) {
			this->leftStop();
			this->rightStop();
			switch (AItype) {
			case 0: // normal
				if (runawayDuration > HIDING_TIME/8) { // 0.125
					runawayEnded = true;
					runawayDuration = 0;
				}
				break;
			case 1: // mild
				if (runawayDuration > (HIDING_TIME/6.5)) { // 0.15
					runawayEnded = true;
					runawayDuration = 0;
				}
				break;
			case 2: // furious
				if (runawayDuration > (HIDING_TIME/10)) { // 0.1
					runawayEnded = true;
					runawayDuration = 0;
				}
				break;
			}
			runawayInterval = 0;
		}
		runawayDuration += deltaTime;
	}
	runawayInterval += deltaTime;
	std::cout << "RUNAWAY INTERVAL: " << runawayInterval << std::endl;
}

void Alien::updateAI(float deltaTime, int xPlayer) {


	static float AIcounter = 0;

	static bool sideMovementDir = false;
	static float laserTimer = 0;

	switch (AItype) {
	case 0: // normal
		if (AIcounter > (ACTION_TIME/1.66)) { // 0.6
			this->makeAction(deltaTime, xPlayer);
			AIcounter = 0;
		}
		break;
	case 1: // mild
		if (AIcounter > (ACTION_TIME/1.25)) { // 0.8
			this->makeAction(deltaTime, xPlayer);
			AIcounter = 0;
		}
		break;
	case 2: // furious
		if (AIcounter > (ACTION_TIME/2.5)) { // 0.4
			this->makeAction(deltaTime, xPlayer);
			AIcounter = 0;
		}
		break;
	}

	if (isFollowing == false && runawayEnded == true) {
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
	this->update(deltaTime, false);
	AIcounter += deltaTime;
}