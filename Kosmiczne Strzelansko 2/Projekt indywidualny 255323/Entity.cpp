#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Resources.h"

Entity::Entity() {
	position.x = 0;
	position.y = 0;
	l = false;
	r = false;
	u = false;
	d = false;
	speed = 0;
}

Entity::Entity(const Entity& copied) {
	this->position = copied.position;
	this->l = copied.l;
	this->r = copied.r;
	this->u = copied.u;
	this->d = copied.d;

	this->sprite = copied.sprite;
	this->texture = copied.texture;
	sprite.setTexture(texture);
	sprite.setPosition(position);

	this->speed = copied.speed;
}

Entity::Entity(Texture entityTexture, float x, float y, float entitySpeed) {
	texture = entityTexture;
	sprite.setTexture(texture);
	this->setPosition(x, y);
	speed = entitySpeed;
}

void Entity::setTexture(Texture entityTexture) {
	texture = entityTexture;
	sprite.setTexture(texture);
	sprite.setOrigin((sprite.getTexture()->getSize().x) / 2, (sprite.getTexture()->getSize().y) / 2);
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