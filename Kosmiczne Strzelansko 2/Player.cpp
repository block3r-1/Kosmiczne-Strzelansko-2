#include <random>

#include "Player.h"

void Player::shootLaser() {

}

Player::Player() {
	speed = 800;
	shakingSpeed = 100;
	lives = 5;
	score = 0;
	laserPower = 5;

	this->setTexture("ship100");
	this->setPosition((VideoMode::getDesktopMode().width / 2) - 100, (VideoMode::getDesktopMode().height - 230));
	

}

void Player::shakeShip() {
	static bool shaking = false;
	static int distance = 0;

	static bool left = false;
	static int counter = 0;
	if (shaking == false) {
		std::random_device seed;
		std::default_random_engine generator(seed());
		std::uniform_int_distribution <int> distribution(0, 150);
		int randomNumber = distribution(seed);
		distance = randomNumber;
		shaking = true;
	}
	else if (shaking == true) {
		if (left == true) {
			this->left();
			if (counter > (distance + 1000)) {
				left = false;
				counter = 0;
			}
		}
		else {
			this->right();
			if (counter > (distance + 1000)) {
				left = true;
				counter = 0;
			}
		}
	}
	counter++;
}

void Player::update(float deltaTime, bool shaking) {
	if (shaking == false) {
		if (l == true) this->moveLeft(speed * deltaTime);
		if (r == true) this->moveRight(speed * deltaTime);
		if (u == true) this->moveUp(speed * deltaTime);
		if (d == true) this->moveDown(speed * deltaTime);
	}
	else {
		if (l == true) this->moveLeft(shakingSpeed * deltaTime);
		if (r == true) this->moveRight(shakingSpeed * deltaTime);
	}
}