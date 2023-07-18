#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "Timer.h"

class Camera {
public:
	static void Follow(GameObject* newFocus);
	static void UnFollow();
	static void Update(float dt);

	static Vec2 pos;
	static Vec2 speed;
	static float shakeTime;

private:
	static GameObject* focus;

	static Timer shakeTimer;
};


#endif // CAMERA_H
