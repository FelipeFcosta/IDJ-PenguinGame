#pragma once
#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H
#include <string>;
#include "GameObject.h"
#include "Component.h"
#include "Timer.h"
#include <memory>


class PenguinCannon : public Component
{
public:
	PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
	~PenguinCannon();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);

	void Shoot();

private:
	std::weak_ptr<GameObject> pbody;
	float angle;
};

#endif // PENGUIN_BODY_H
