#include <SFML/Graphics.hpp>

#include "Entity.h"

void Entity::setTexture(std::string textureName) {

	std::string texturePath = "textures\\" + textureName + ".png";
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);

	sprite.setOrigin(position);
}

void Entity::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

Vector2<float> Entity::getPosition() {
	return position;
}

Sprite Entity::getSprite() { 
	return sprite;
}

void Entity::left() {
	l = true;
}

void Entity::right() {
	r = true;
}

void Entity::up() {
	u = true;
}

void Entity::down() {
	d = true;
}

void Entity::leftStop() {
	l = false;
}

void Entity::rightStop() {
	r = false;
}

void Entity::upStop() {
	u = false;
}

void Entity::downStop() {
	d = false;
}

void Entity::moveUp(float distance) {
	position.y -= distance;
	sprite.setPosition(position);
}

void Entity::moveDown(float distance) {
	position.y += distance;
	sprite.setPosition(position);
}

void Entity::moveLeft(float distance) {
	position.x -= distance;
	sprite.setPosition(position);
}

void Entity::moveRight(float distance) {
	position.x += distance;
	sprite.setPosition(position);
}

void Entity::update(float deltaTime) {
	if (l == true) this->moveLeft(speed * deltaTime);
	if (r == true) this->moveRight(speed * deltaTime);
	if (u == true) this->moveUp(speed * deltaTime);
	if (d == true) this->moveDown(speed * deltaTime);
}