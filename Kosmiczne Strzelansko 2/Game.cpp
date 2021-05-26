#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Player.h"

Game::Game() {

	// pobranie rozdzielczosci ekranu
	Vector2 <int> screenResolution;
	screenResolution.x = VideoMode::getDesktopMode().width;
	screenResolution.y = VideoMode::getDesktopMode().height;
	
	// otwarcie okna
	gameWindow.create(VideoMode(screenResolution.x, screenResolution.y), "KOSMICZNE STRZELANSKO"); //Style::Fullscreen);
	backgroundScreenTexture.loadFromFile("textures\\background16x.png");
	backgroundScreen.setTexture(backgroundScreenTexture);

}

Game::~Game() {

}

void Game::getPlayerInput() {

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.left();
	}
	else {
		player.leftStop();
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.right();
	}
	else {
		player.rightStop();
	}

	while (gameWindow.pollEvent(event)) {
		if (event.type == Event::Closed) gameWindow.close();
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) gameWindow.close();

		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) player.moveUp(5);
		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) player.moveDown(5);
		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) player.moveLeft(5);
		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) player.moveRight(5);
	}
}

void Game::drawWindowElements() {
	gameWindow.draw(backgroundScreen);
	gameWindow.draw(player.getSprite());
}

void Game::updateGameState(float deltaTime) {
	static bool shaking = false;
	if (shaking == true) {
		player.shakeShip();
	}
	player.update(deltaTime, shaking);
	shaking = !shaking;
}

void Game::startGame() {
	while (gameWindow.isOpen()) {
		Time deltaTime = gameClock.restart();

		this->getPlayerInput();
		this->updateGameState(deltaTime.asSeconds());
		this->drawWindowElements();

		gameWindow.display();
	}
}