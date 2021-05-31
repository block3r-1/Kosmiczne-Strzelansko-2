#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Windows.h>

#include "Game.h"
#include "Player.h"
#include "Resources.h"
#include "Asteroid.h"
#include "Alien.h"

#define LASER_SPEED 0.3
#define ASTEROID_COUNT 40
#define LASER_VELOCITY 700

Game::Game() {
	// zaladowanie calej bazy danych
	resourceContainer.loadPlayerTexture("papaj");
	resourceContainer.loadSecondPlayerTexture("papajzly");
	resourceContainer.loadAlienTexture("papajokrutnik");
	resourceContainer.loadBackgroundTexture("background16x");
	resourceContainer.loadLaserTexture("kremowka");
	resourceContainer.loadAsteroidTexture("pudzian40");
	//resourceContainer.loadFont("impact");
	textFont.loadFromFile("fonts\\ca.ttf");

	// inicjalizacja gracza i kosmity
	player.setTexture(resourceContainer.getPlayerTexture());
	player.setPosition((VideoMode::getDesktopMode().width / 2), (VideoMode::getDesktopMode().height - 100));

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

	// inicjalizacja wszystkich obiektow tekstowych
	logo.setFont(textFont);
	score.setFont(textFont);
	lives.setFont(textFont);

	logo.setString("KOSMICZNE STRZELANSKO 2");
	logo.setCharacterSize(100);
	logo.setFillColor(Color::Green);
	logo.setStyle(Text::Italic);
	logo.setOrigin(logo.getGlobalBounds().width / 2, logo.getGlobalBounds().height / 2);
	logo.setPosition(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);

	score.setCharacterSize(50);
	//score.setOrigin(score.getGlobalBounds().width / 2, score.getGlobalBounds().height / 2);
	score.setPosition(30, (VideoMode::getDesktopMode().height - 70));
	score.setFillColor(Color::Green);

	lives.setCharacterSize(50);
	//lives.setOrigin(lives.getGlobalBounds().width / 2, lives.getGlobalBounds().height / 2);
	lives.setPosition((VideoMode::getDesktopMode().width - 450), (VideoMode::getDesktopMode().height - 70));
	lives.setFillColor(Color::Red);
}

Game::~Game() {
	delete[] asteroids;
}

void Game::startScreen() {
	gameWindow.draw(backgroundScreen);
	gameWindow.draw(logo);
	gameWindow.display();
	//Sleep(5000);
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
	score.setString("SCORE: " + std::to_string(player.getScore()));
	lives.setString("LIVES: " + std::to_string(player.getLives()));
	gameWindow.draw(score);
	gameWindow.draw(lives);
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

	// lasery kosmity i gracz
	for (int i = 0; i < alien.getLaserCount(); i++) {
		laserBox = alien.getLaserBounds(i);
			if (laserBox.intersects(player.getSprite().getGlobalBounds())) {
				player.decreaseLives();
				alien.destroyLaser(i);
			}
		}

	// asteroidy i asteroidy
	FloatRect secondAsteroidBox;
	for (int i = 0; i < ASTEROID_COUNT; i++) {
		asteroidBox = asteroids[i].getSprite().getGlobalBounds();
		// asteroidy i gracz
		if (asteroidBox.intersects(player.getSprite().getGlobalBounds())) {
			player.decreaseLives();
			asteroids[i].setPosition(-500, -500);
		}
		// asteroidy i asteroidy c.d.
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
	alien.updateAI(deltaTime, player.getPosition().x);
}

void Game::startGame() {
	this->startScreen();
	while (gameWindow.isOpen()) {
		Time deltaTime = gameClock.restart();

		this->getPlayerInput();
		this->collisionDetection();
		this->updateGameState(deltaTime.asSeconds());
		this->drawWindowElements();

		gameWindow.display();
	}
}