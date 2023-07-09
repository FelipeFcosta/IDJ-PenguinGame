#include "Face.h"
#include "Sound.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>


Face::Face(GameObject& associated) : Component(associated), hitPoints(30) {}

void Face::Damage(int damage) {
	hitPoints -= damage;

	if (hitPoints <= 0) {
		if (!associated.IsDead()) {
			associated.RequestDelete();
			Sound* associatedSound = (Sound*)associated.GetComponent("Sound");
			if (associatedSound != nullptr && associatedSound->IsOpen()) {
				associatedSound->Play();
			}
		}
	}
}

void Face::Update(float dt) {
	InputManager& input = InputManager::GetInstance();

	if (input.MousePress(LEFT_MOUSE_BUTTON)) {
		Vec2 clickedPos((float)input.GetMouseX(), (float)input.GetMouseY());
		if (associated.box.Contains(clickedPos)) {
			Damage(std::rand() % 10 + 10);
		}
	}

	// antes de adicionar considerar a camera no render
	//if (input.IsKeyDown(LEFT_ARROW_KEY))
	//	associated.box.x += Camera::speed.x*dt;
	//if (input.IsKeyDown(RIGHT_ARROW_KEY))
	//	associated.box.x -= Camera::speed.x*dt;
	//if (input.IsKeyDown(UP_ARROW_KEY))
	//	associated.box.y += Camera::speed.y*dt;
	//if (input.IsKeyDown(DOWN_ARROW_KEY))
	//	associated.box.y -= Camera::speed.y*dt;
}

void Face::Render() {
}

bool Face::Is(std::string type) {
	return type == "Face";
}
