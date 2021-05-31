#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Player.h"
#include "Resources.h"
#include "Asteroid.h"
#include "Alien.h"

#define LASER_SPEED 0.3
#define ASTEROID_COUNT 40
#define LASER_VELOCITY 700

Game::Game() {

	resourceContainer.loadPlayerTexture("papaj");
	resourceContainer.loadSecondPlayerTexture("papajzly");
	resourceContainer.loadAlienTexture("papajokrutnik");
	resourceContainer.loadBackgroundTexture("background16x");
	resourceContainer.loadLaserTexture("kremowka");
	resourceContainer.loadAsteroidTexture("pudzian40");

	player.setTexture(resourceContainer.getPlayerTexture());
	player.setPosition((VideoMode::getDesktopMode().width / 2) - 100, (VideoMode::getDesktopMode().height - 180));

	player.setLaserTexture(resourceContainer.getLaserTexture());

	alien.setTexture(resourceContainer.getAlienTexture());
	alien.setPosition(500, 100);

	alien.setLaserTexture(resourceContainer.getLaserTexture());

	// pobranie rozdzielczosci ekranu
	Vector2 <int> screenResolution;
	screenResolution.x = VideoMode::getDesktopMode().width;
	screenResolution.y = VideoMode::getDesktopMode().height;
	
	// otwarcie okna
	gameWindow.create(VideoMode(screenResolution.x, screenResolution.y), "KOSMICZNE STRZELANSKO"); //Style::Fullscreen);
	backgroundScreenTexture = resourceContainer.getBackgroundTexture();
	backgroundScreen.setTexture(backgroundScreenTexture);

	// stworzenie tablicy na asteroidy
	asteroids = new Asteroid[ASTEROID_COUNT];
	for (int i = 0; i < ASTEROID_COUNT; i++) {
		asteroids[i].setTexture(resourceContainer.getAsteroidTexture());
	}
}

Game::~Game() {
	delete[] asteroids;
}

void Game::getPlayerInput() {
	// ruch w lewo
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.left();
	}
	else {
		player.leftStop();
	}

	// ruch w prawo
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.right();
	}
	else {
		player.rightStop();
	}

	// strzal laserem
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		player.shootLaser();
		player.setTexture(resourceContainer.getSecondPlayerTexture());
	}
	else {
		player.stopLaser();
		player.setTexture(resourceContainer.getPlayerTexture());
	}

	// wyjscie z gry
	while (gameWindow.pollEvent(event)) {
		if (event.type == Event::Closed) gameWindow.close();
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) gameWindow.close();
	}
}

void Game::drawWindowElements() {
	gameWindow.draw(backgroundScreen);
	gameWindow.draw(player.getSprite());
	int laserCount = player.getLaserCount();
	for (int i = 0; i < laserCount; i++) {
		gameWindow.draw(player.getLaserSprite(i));
	}
	for (int i = 0; i < ASTEROID_COUNT; i++) {
		gameWindow.draw(asteroids[i].getSprite());

	}
	gameWindow.draw(alien.getSprite());
	int alienLaserCount = alien.getLaserCount();
	for (int i = 0; i < alienLaserCount; i++) {
		gameWindow.draw(alien.getLaserSprite(i));
	}
}

void Game::collisionDetection() {
	FloatRect asteroidBox;
	FloatRect laserBox;

	// asteroidy i lasery
	for (int i = 0; i < player.getLaserCount(); i++) {
		laserBox = player.getLaserBounds(i);
			for (int j = 0; j < ASTEROID_COUNT; j++) {
				asteroidBox = asteroids[j].getSprite().getGlobalBounds();
				if (laserBox.intersects(asteroidBox)) {
					asteroids[j].setPosition(-500, -500);
				}
			}
	}

	// asteroidy i asteroidy
	FloatRect secondAsteroidBox;
	for (int i = 0; i < ASTEROID_COUNT; i++) {
		asteroidBox = asteroids[i].getSprite().getGlobalBounds();
		if (asteroidBox.intersects(player.getSprite().getGlobalBounds())) {
			player.decreaseLives();
			asteroids[i].setPosition(-500, -500);
		}
		for (int j = 0; j < ASTEROID_COUNT; j++) {
			secondAsteroidBox = asteroids[j].getSprite().getGlobalBounds();
			if (asteroidBox.intersects(secondAsteroidBox)) {
				if (asteroidBox == secondAsteroidBox) break;
				asteroids[i].hit();
				asteroids[j].hit();
			}
		}
	}
}

void Game::updateGameState(float deltaTime) {
	static bool shaking = false;
	static float laserTimer = 0;
	if (shaking == true) {
		player.shakeShip();
	}
	if (player.getLaserState() == true) {
		if (laserTimer > LASER_SPEED) {
			player.generateLaserInstance(LASER_VELOCITY);
			laserTimer = 0;
		}
	}
	laserTimer += deltaTime;
	player.update(deltaTime, shaking);
	player.updateLasers(deltaTime);
	shaking = !shaking;
	for (int i = 0; i < ASTEROID_COUNT; i++) {
		asteroids[i].update(deltaTime);
	}
	alien.updateAI(deltaTime, player.getPosition().x, shaking);
}

void Game::startGame() {
	while (gameWindow.isOpen()) {
		Time deltaTime = gameClock.restart();

		this->getPlayerInput();
		this->collisionDetection();
		this->updateGameState(deltaTime.asSeconds());
		this->drawWindowElements();

		gameWindow.display();
	}
}