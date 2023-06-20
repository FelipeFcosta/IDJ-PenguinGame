#pragma once
#ifndef ALIEN_H
#define ALIEN_H
#include "GameObject.h"
#include "Component.h"
#include <vector>
#include <queue>
#include <memory>

// mouse-controlled enemy
class Alien : public Component
{
public:
	Alien(GameObject& associated, int nMinions);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);

private:
	class Action
	{
	public:
		enum ActionType { MOVE, SHOOT };		
		Action(ActionType type, float x, float y);

		ActionType type;
		Vec2 pos;
	};

	Vec2 speed;
	int hp;
	float rotationAngle;
	std::queue<Action> taskQueue;	// every click is an Action to be queued
	std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif // ALIEN_H
