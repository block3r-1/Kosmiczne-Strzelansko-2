#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Player.h"

using namespace sf;

class Game {
	// backend i logika gry
	RenderWindow gameWindow;
	Clock gameClock;
	Event event;

	// tlo glownej planszy
	Texture backgroundScreenTexture;
	Sprite backgroundScreen;

	// rozgrywka
	Player player;

public:
	void getPlayerInput();
	void updateGameState(float deltaTime);
	void drawWindowElements();
	void startGame();

	Game();
	~Game();
};