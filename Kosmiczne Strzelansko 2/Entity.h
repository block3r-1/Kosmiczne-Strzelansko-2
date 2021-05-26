#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
protected:
	// pozycja na mapie
	Vector2 <float> position;
	bool l; //left
	bool r; //right
	bool u; //up
	bool d; //down

	// wyswietlanie obiektu
	Texture texture;
	Sprite sprite;

	// wlasciwosci rozgrywki
	float speed;
public:
	void setTexture(std::string textureName);
	void setPosition(float x, float y);
	Vector2<float> getPosition();
	Sprite getSprite();
	void left();
	void right();
	void up();
	void down();
	void leftStop();
	void rightStop();
	void upStop();
	void downStop();
	void moveUp(float distance);
	void moveDown(float distance);
	void moveLeft(float distance);
	void moveRight(float distance);
	void update(float deltaTime);
};