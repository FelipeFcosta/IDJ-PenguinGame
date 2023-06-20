#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include <string>
#include "Vec2.h"


class Bullet : public Component
{
public:
	Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	int GetDamage();

private:
	int damage;
	float distanceLeft;
	Vec2 speed;
};

#endif // BULLET_H
