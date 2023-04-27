#pragma once
#ifndef FACE_H
#define FACE_H

#include "GameObject.h"
#include "Component.h"

// an "enemy" of our penguim game, with HP
class Face : public Component
{
public:
	Face(GameObject& associated);
	void Damage(int damage);
	void Update(float dt);
	void Render();
	bool Is(std::string type);

private:
	int hitPoints;
};

#endif // FACE_H
