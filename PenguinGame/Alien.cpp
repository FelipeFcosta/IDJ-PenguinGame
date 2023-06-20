#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include <iostream>
#include <memory>

#define HP 10
#define	ALIEN_SPEED 200
#define ALIEN_ROTATION_SPEED  (.03f) * 2.0f * (float) M_PI
#define	QTD_MINIONS 3

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), speed(0, 0), hp(HP), rotationAngle(0) {
	Sprite* alienSprite = new Sprite(associated, "resources/img/alien.png");
	associated.AddComponent(alienSprite);
}

Alien::~Alien() {
	// clear minionArray
	minionArray.clear();
}

void Alien::Start() {
	// populate minionArray
	State &gameState = Game::GetInstance().GetState();
	for (int i = 0; i < QTD_MINIONS; i++) {
		GameObject* minionObj = new GameObject();
		Minion *minion = new Minion(*minionObj, gameState.GetObjectPtr(&associated), i * (360.0f/QTD_MINIONS));
		Sprite *minionSprite = (Sprite*)minionObj->GetComponent("Sprite");

		double scale = ((double)rand() / RAND_MAX) / 2.0f + 1;	// random number between 1 and 1.5
		minionSprite->SetScale(scale, scale);

		minionObj->AddComponent(minion);
		minionArray.emplace_back(gameState.AddObject(minionObj));
	}
}

void Alien::Update(float dt) {
	InputManager& input = InputManager::GetInstance();

	Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
	sprite->SetAngleDeg(rotationAngle * 180.0f/ (float) M_PI);
	rotationAngle -= ALIEN_ROTATION_SPEED * dt;

	if (input.MousePress(LEFT_MOUSE_BUTTON)) {
		Action shoot(Action::SHOOT, input.GetMouseX(), input.GetMouseY());
		taskQueue.push(shoot);
	} else if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
		Action move(Action::MOVE, input.GetMouseX() - associated.box.w/2,
			input.GetMouseY() - associated.box.h/2);
		taskQueue.push(move);
	}

	if (!taskQueue.empty()) {
		Action action = taskQueue.front();

		if (action.type == Action::SHOOT) {

			if (minionArray.size() > 0) {
				auto minionObj = minionArray[rand() % minionArray.size()].lock();
				Minion* minion = (Minion*)minionObj->GetComponent("Minion");
			
				minion->Shoot(action.pos);
				taskQueue.pop();
			}

		} else if (action.type == Action::MOVE) {
			Vec2 actionAlienDist = Vec2::Subtract(action.pos, { associated.box.x, associated.box.y });

			speed.x = ALIEN_SPEED * Vec2::Normalize(actionAlienDist).x;
			speed.y = ALIEN_SPEED * Vec2::Normalize(actionAlienDist).y;
			
			associated.box.x += speed.x*dt;
			associated.box.y += speed.y*dt;
		}

		float associatedX = associated.box.x;
		float associatedY = associated.box.y;
		float epsilon = 10;

		if (abs(associatedX - action.pos.x) <= epsilon && abs(associatedY - action.pos.y) <= epsilon) {
			taskQueue.pop();
		}
	}

}

void Alien::Render() {
}

bool Alien::Is(std::string type) {
	return type == "Alien";
}

Alien::Action::Action(ActionType type, float x, float y) : pos(x, y), type(type) {}
