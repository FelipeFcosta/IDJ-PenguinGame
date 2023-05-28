#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

#define SPEED 300

GameObject* Camera::focus = nullptr;
Vec2 Camera::speed = Vec2(SPEED, SPEED);
Vec2 Camera::pos = Vec2(0, 0);

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::UnFollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if (focus != nullptr) {
		pos.x = focus->box.x - GAME_WIDTH/2;
		pos.y = focus->box.y - GAME_HEIGHT/2;
	}
	else {
		InputManager& inputManager = InputManager::GetInstance();

		if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
			pos.x -= speed.x * dt;
		}
		if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
			pos.x += speed.x * dt;
		}
		if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
			pos.y -= speed.y * dt;
		}
		if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
			pos.y += speed.y * dt;
		}
	}
}
