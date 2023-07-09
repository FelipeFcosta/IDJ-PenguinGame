#pragma once
#ifndef ALIEN_H
#define ALIEN_H
#include "GameObject.h"
#include "Component.h"
#include "Timer.h"
#include <vector>
#include <queue>
#include <memory>

#define DEFAULT_QTD_MINIONS 3

// mouse-controlled enemy
class Alien : public Component
{
public:
	Alien(GameObject& associated, int nMinions);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

	static int alienCount;

private:
	Vec2 speed;
	int hp;
	int nMinions;
	float rotationAngle;
	std::vector<std::weak_ptr<GameObject>> minionArray;
	Timer damageTimer;


	enum AlienState { MOVING, RESTING };
	AlienState state;

	Timer restTimer;
	Vec2 destination;

};

#endif // ALIEN_H
