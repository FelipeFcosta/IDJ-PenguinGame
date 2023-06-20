#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include "GameObject.h"

class Component
{
public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Start() {};
	bool virtual Is(std::string type) = 0;

protected:
	GameObject& associated;
};

#endif  // COMPONENT_H