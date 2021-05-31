#pragma once

#include "Player.h"

class Alien : public Player {
	int AItype; // 0 - normal, 1 - calm, 2 - furious
	int laserSpeed;

	bool isFollowing;
	bool sideMovement;

	bool runawayEnded;

public:
	Alien();
	void follow(int xPlayer);
	void runAway(bool direction);
	void makeAction(float deltaTime, int xPlayer);
	void destroyLaser(int number);
	void updateLasers(float deltaTime);
	void updateAI(float deltaTime, int xPlayer);
};