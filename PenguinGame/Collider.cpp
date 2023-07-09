#include "Collider.h"
#include "Collision.h"
#include "Sprite.h"
#include "InputManager.h"

#include "Camera.h"
#include "Game.h"
#include "SDL.h"

bool showBoxes = false;

void Collider::Render() {
	if (showBoxes) {
		Vec2 center(box.GetCenter());
		SDL_Point points[5];

		Sprite* associatedSprite = (Sprite*)associated.GetComponent("Sprite");
		float associatedAngle = associatedSprite ? associatedSprite->GetAngleDeg() : 0;

		Vec2 point = Vec2::Rotate(Vec2(box.x, box.y) - center, associatedAngle / (180/M_PI)) + center - Camera::pos;
		points[0] = { (int)point.x, (int)point.y };
		points[4] = { (int)point.x, (int)point.y };

		point = Vec2::Rotate(Vec2(box.x + box.w, box.y) - center, associatedAngle / (180/M_PI)) + center - Camera::pos;
		points[1] = { (int)point.x, (int)point.y };

		point = Vec2::Rotate(Vec2(box.x + box.w, box.y + box.h) - center, associatedAngle / (180/M_PI))	+ center - Camera::pos;
		points[2] = { (int)point.x, (int)point.y };

		point = Vec2::Rotate(Vec2(box.x, box.y + box.h) - center, associatedAngle / (180/M_PI))	+ center - Camera::pos;
		points[3] = { (int)point.x, (int)point.y };

		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
	}
}


Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {}


void Collider::Update(float dt) {
	InputManager& input = InputManager::GetInstance();
	if (input.KeyPress(B_KEY)) {
		showBoxes = !showBoxes;
		input.Update();
	}

	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;

	box.x = associated.box.x + offset.x;
	box.y = associated.box.y + offset.y;

	Sprite* associatedSprite = (Sprite*)associated.GetComponent("Sprite");
	if (associatedSprite != nullptr) {
		double angle = associatedSprite->GetAngleDeg();
		Vec2::Rotate({ box.x, box.y }, angle);
	}

}

void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset(Vec2 scale) {
	this->offset = offset;
}

bool Collider::Is(std::string type) {
	return type == "Collider";
}