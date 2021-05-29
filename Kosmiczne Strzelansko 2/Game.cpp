#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Player.h"
#include "Resources.h"

#define LASER_SPEED 0.3

Game::Game() {

	resourceContainer.loadPlayerTexture("papaj");
	resourceContainer.loadBackgroundTexture("background16x");
	resourceContainer.loadLaserTexture("kremowka");
	resourceContainer.loadAsteroidTexture("pudzian40");

	player.setTexture(resourceContainer.getPlayerTexture());
	player.setPosition((VideoMode::getDesktopMode().width / 2) - 100, (VideoMode::getDesktopMode().height - 230));

	player.setLaserTexture(resourceContainer.getLaserTexture());

	// pobranie rozdzielczosci ekranu
	Vector2 <int> screenResolution;
	screenResolution.x = VideoMode::getDesktopMode().width;
	screenResolution.y = VideoMode::getDesktopMode().height;
	
	// otwarcie okna
	gameWindow.create(VideoMode(screenResolution.x, screenResolution.y), "KOSMICZNE STRZELANSKO"); //Style::Fullscreen);
	backgroundScreenTexture = resourceContainer.getBackgroundTexture();
	backgroundScreen.setTexture(backgroundScreenTexture);

	//stworzeie tablicy na asteroidy
	asteroids = new Asteroid[5];
	for (int i = 0; i < 5; i++) {
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
	}
	else {
		player.stopLaser();
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
	for (int i = 0; i < 5; i++) {
		gameWindow.draw(asteroids[i].getSprite());
	}
}

void Game::collisionDetection() {
	FloatRect asteroidBox;
	FloatRect laserBox;
	for (int i = 0; i < player.getLaserCount(); i++) {
		laserBox = player.getLaserBounds(i);
			for (int j = 0; j < 5; j++) {
				asteroidBox = asteroids[j].getSprite().getGlobalBounds();
				if (laserBox.intersects(asteroidBox)) {
					asteroids[j].setPosition(-500, -500);
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
			player.generateLaserInstance();
			laserTimer = 0;
		}
	}
	laserTimer += deltaTime;
	player.update(deltaTime, shaking);
	shaking = !shaking;
	for (int i = 0; i < 5; i++) {
		asteroids[i].update(deltaTime);
	}

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