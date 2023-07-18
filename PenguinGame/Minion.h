#pragma once
#ifndef MINION_H
#define MINION_H
#include "GameObject.h"
#include "Component.h"
#include "Timer.h"
#include <memory>

// minions be circling the alien
class Minion : public Component
{
public:
	Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0, float speedFactor = 1);

	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Shoot(Vec2 target);
	void NotifyCollision(GameObject& other);

private:
	std::weak_ptr<GameObject> alienCenter;
	float arc;
	Timer damageTimer;
	float speedFactor;
};


#endif // MINION_H
