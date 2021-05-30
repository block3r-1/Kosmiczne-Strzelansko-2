#pragma once

#include "Player.h"

class Alien : public Player {
	int AItype; // 0 - normal, 1 - calm, 2 - furious

	bool isFollowing;
	bool sideMovement;

	bool runawayEnded;
	bool hideNSeek;


	bool mildShooting;
	bool furiousShooting;
	bool replyShooting;
public:
	Alien();
	void follow(int xPlayer);
	void runAway();
	void sideToSide(int direction);
	void hideAndSeek();
	void updateLasers(float deltaTime);
	void updateAI(float deltaTime, int xPlayer, bool shaking);
};