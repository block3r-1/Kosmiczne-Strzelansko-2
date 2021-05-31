#include <random>

#include "Player.h"
#include "Resources.h"

void Player::setLaserTexture(Texture newLaserTexture) {
	laserTexture = newLaserTexture;
}

void Player::shootLaser() {
	laserShot = true;
}

void Player::stopLaser() {
	laserShot = false;
}

bool Player::getLaserState() {
	return laserShot;
}
void Player::generateLaserInstance(int laserSpeed) {
	if (laserShot == false) return;

	Entity laser(laserTexture, sprite.getPosition().x, sprite.getPosition().y, laserSpeed);
	playerLasers.push_back(laser);

}

Player::Player() {
	speed = 800;
	shakingSpeed = 100;
	lives = 50;
	score = 0;

	laserShot = false;
	l = false;
	r = false;
	u = false;
	d = false;

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
			if (counter > (distance + 200)) {
				left = false;
				counter = 0;
			}
		}
		else {
			this->right();
			if (counter > (distance + 200)) {
				left = true;
				counter = 0;
			}
		}
	}
	counter++;
}

void Player::update(float deltaTime, bool shaking) {
	if (shaking == false) {
		if (l == true) {
			//if (position.x < 0) return;
			this->moveLeft(speed * deltaTime);
		}
		if (r == true) {
			//if (position.x > (VideoMode::getDesktopMode().width - sprite.getGlobalBounds().width)) return;
			this->moveRight(speed * deltaTime);
		}
		if (u == true) this->moveUp(speed * deltaTime);
		if (d == true) this->moveDown(speed * deltaTime);
	}
	else {
		if (l == true) {
			//if (position.x < 0) return;
			this->moveLeft(shakingSpeed * deltaTime);
		}
		if (r == true) {
			//if (position.x > (VideoMode::getDesktopMode().width - sprite.getGlobalBounds().width)) return;
			this->moveRight(shakingSpeed * deltaTime);
		}
	}
}

void Player::updateLasers(float deltaTime) {
	if (playerLasers.empty() == true) return;

	auto laserIterator = playerLasers.begin();
	while (laserIterator != playerLasers.end()) {
		laserIterator->setTexture(laserTexture);
		laserIterator->up();
		laserIterator->update(deltaTime);
		if (laserIterator->getPosition().y < 0) {
			laserIterator = playerLasers.erase(laserIterator);
		}
		else {
			laserIterator++;
		}
	}
}

Sprite Player::getLaserSprite(int number) {
	Sprite empty;
	if (playerLasers.empty() == true) return empty;

	return playerLasers[number].getSprite();
}

int Player::getLaserCount() {
	return playerLasers.size();
}

FloatRect Player::getLaserBounds(int number) {
	return playerLasers[number].getSprite().getGlobalBounds();
}

void Player::decreaseLives() {
	lives -= 5;
}

int Player::getScore() {
	return score;
}

int Player::getLives() {
	return lives;
}