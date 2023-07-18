#pragma once
#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H
#include <string>
#include <memory>
#include "GameObject.h"
#include "Timer.h"
#include "Component.h"


class PenguinBody : public Component
{
public:
	PenguinBody(GameObject& associated);
	~PenguinBody();
	void Start();
	void Update(float dt);
    void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	
	static PenguinBody* player;
	Vec2 position;

private:
	std::weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed;
	float angle;
	int hp;
	Timer damageTimer;
	Timer endTimer;
	bool penguinDead;
};

#endif // PENGUIN_BODY_H
