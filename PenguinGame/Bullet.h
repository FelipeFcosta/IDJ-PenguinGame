#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include <string>
#include "Vec2.h"


class Bullet : public Component
{
public:
	Bullet(GameObject& associated, int frameCount, float frameTime, float angle, float speed,
		int damage,float maxDistance, std::string sprite, bool targetedAtPlayer);
	void Update(float dt);
	void Render();
	int GetDamage();
	void NotifyCollision(GameObject& other);

	bool Is(std::string type);
	
	bool targetedAtPlayer;

private:
	int damage;
	float distanceLeft;
	Vec2 speed;
};

#endif // BULLET_H
