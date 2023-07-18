#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

#define	SPEED 300

GameObject* Camera::focus = nullptr;
Vec2 Camera::speed = Vec2(SPEED, SPEED);
Vec2 Camera::pos = Vec2(0, 0);
float Camera::shakeTime = 0;
Timer Camera::shakeTimer = Timer();

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::UnFollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if (focus != nullptr) {
		pos.x = focus->box.x - GAME_WIDTH / 2;
		pos.y = focus->box.y - GAME_HEIGHT / 2;

		if (shakeTime > 0) {
			shakeTimer.Update(dt);
			if (shakeTimer.Get() < shakeTime) {
				bool xPositive = (rand() % 2) == 1;
				bool yPositive = (rand() % 2) == 1;
				pos.x += xPositive ? 2 : -2;
				pos.x += yPositive ? 2 : -2;
			} else {
				shakeTimer.Restart();
				shakeTime = 0;
			}
		}
	} else {
		InputManager& input = InputManager::GetInstance();

		if (input.IsKeyDown(LEFT_ARROW_KEY)) {
			pos.x -= speed.x * dt;
		}
		if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
			pos.x += speed.x * dt;
		}
		if (input.IsKeyDown(UP_ARROW_KEY)) {
			pos.y -= speed.y * dt;
		}
		if (input.IsKeyDown(DOWN_ARROW_KEY)) {
			pos.y += speed.y * dt;
		}
	}
}
