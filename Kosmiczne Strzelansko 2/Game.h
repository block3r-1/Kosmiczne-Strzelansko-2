#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Player.h"
#include "Resources.h"
#include "Asteroid.h"

using namespace sf;

class Game {
	// backend i logika gry
	RenderWindow gameWindow;
	Clock gameClock;
	Event event;
	Resources resourceContainer;

	// tlo glownej planszy
	Texture backgroundScreenTexture;
	Sprite backgroundScreen;

	// rozgrywka
	Player player;
	Asteroid* asteroids;

public:
	void getPlayerInput();
	void updateGameState(float deltaTime);
	void collisionDetection();
	void drawWindowElements();
	void startGame();

	Game();
	~Game();
};