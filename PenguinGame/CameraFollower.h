#pragma once
#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include "GameObject.h"
#include "Component.h"
#include "Camera.h"
#include <iostream>

class CameraFollower : public Component
{
public:
	CameraFollower(GameObject& associated);

	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif // CAMERA_FOLLOWER_H
