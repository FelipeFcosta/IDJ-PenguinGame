#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "Alien.h"
#include <iostream>

Bullet::Bullet(GameObject& associated, int frameCount, float frameTime, float angle, float speed, int damage,
		float maxDistance, std::string sprite, bool targetedAtPlayer) : Component(associated), speed({speed, 0}) {
	Sprite* bulletSprite = new Sprite(associated, sprite, frameCount, frameTime);
	Collider* bulletCollider = new Collider(associated);
	associated.AddComponent(bulletSprite);
	associated.AddComponent(bulletCollider);

	this->speed = Vec2::Rotate(this->speed, angle);

	this->damage = damage;
	this->distanceLeft = maxDistance;
	this->targetedAtPlayer = targetedAtPlayer;
}

void Bullet::Update(float dt) {
	distanceLeft -= Vec2::Magnitude(speed)*dt;
	if (distanceLeft > 0) {
		associated.box.x += speed.x * dt;
		associated.box.y += speed.y * dt;
	} else {
		associated.RequestDelete();
	}

}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
	auto penguinBody = (PenguinBody*)other.GetComponent("PenguinBody");
	auto alien = (Alien*)other.GetComponent("Alien");
	auto minion = (Alien*)other.GetComponent("Minion");

	if (penguinBody && targetedAtPlayer || (alien || minion) && !targetedAtPlayer) {
		associated.RequestDelete();
	}

}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
	return type == "Bullet";
}
