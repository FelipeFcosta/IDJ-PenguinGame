#pragma once
#include "Component.h"
#include "GameObject.h"
#ifndef COLLIDER_H

class Collider : public Component
{
public:
	Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetScale(Vec2 scale);
	void SetOffset(Vec2 scale);

	Rect box;


private:
	Vec2 scale, offset;

};

#endif // COLLIDER_H
