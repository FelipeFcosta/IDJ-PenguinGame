#include "Alien.h"
#include "Game.h"
#include "Sprite.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "Bullet.h"

#include <iostream>
#include <memory>

#define HP 2000
#define	ALIEN_SPEED 150
#define ALIEN_ROTATION_SPEED  (.03f) * 2.0f * (float) M_PI
#define ALIEN_REST_TIME 1
#define BULLET_DAMAGE 0.1*HP

int Alien::alienCount;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated),
		speed(0, 0), hp(HP), rotationAngle(0), nMinions(nMinions), destination({0, 0}) {
	Sprite* alienSprite = new Sprite(associated, "resources/img/alien.png", 2, 0);
	Collider* alienCollider = new Collider(associated, {0.65, 0.6}, {20, 40});
	associated.AddComponent(alienSprite);
	associated.AddComponent(alienCollider);
	damageTimer = Timer();
	alienCount++;
	state = Alien::RESTING;
}

Alien::~Alien() {
	// clear minionArray
	minionArray.clear();
}

void Alien::Start() {
	// populate minionArray
	State &gameState = Game::GetInstance().GetState();
	for (int i = 0; i < nMinions; i++) {
		GameObject* minionObj = new GameObject();
		Minion *minion = new Minion(*minionObj, gameState.GetObjectPtr(&associated), i * (360.0f/nMinions));
		Sprite *minionSprite = (Sprite*)minionObj->GetComponent("Sprite");

		float scale = ((float)rand() / RAND_MAX) / 2.0f + 1;	// random number between 1 and 1.5
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

	int epsilon = 10;
	// Alien AI
	if (PenguinBody::player) {
		switch (state)
		{
		case Alien::MOVING:
			if (abs(associated.box.x - destination.x) <= epsilon && abs(associated.box.y - destination.y) <= epsilon) {
				if (minionArray.size() > 0) {
					destination = PenguinBody::player->position;
					auto minionObj = minionArray[rand() % minionArray.size()].lock();
					Minion* minion = (Minion*)minionObj->GetComponent("Minion");
					minion->Shoot(destination);
					restTimer.Restart();
				}
				state = Alien::RESTING;
			}
			else {
				Vec2 distanceVec = destination - Vec2({ associated.box.x, associated.box.y });
				speed.x = ALIEN_SPEED * Vec2::Norm(distanceVec).x;
				speed.y = ALIEN_SPEED * Vec2::Norm(distanceVec).y;
				associated.box.x += speed.x * dt;
				associated.box.y += speed.y * dt;
			}
			break;
		case Alien::RESTING:
			if (restTimer.Get() >= ALIEN_REST_TIME) {
				destination = PenguinBody::player->position;
				state = Alien::MOVING;
			}
			else {
				restTimer.Update(dt);
			}
			break;
		default:
			break;
		}
	}

	if (hp <= 0) {
		GameObject* deathObj = new GameObject();
		Sprite* deathSprite = new Sprite(*deathObj, "resources/img/aliendeath.png", 4, 0.3, { 1, 1 }, 4*0.3);
		deathObj->box.x = associated.box.x;
		deathObj->box.y = associated.box.y;
		deathObj->AddComponent(deathSprite);
		Sound* deathSound = new Sound(*deathObj, "resources/audio/boom.wav");
		deathSound->Play(1);
		deathObj->AddComponent(deathSound);
		Game::GetInstance().GetState().AddObject(deathObj);

		associated.RequestDelete();
	}

	if (sprite->GetFrame() == 1 && damageTimer.Get() >= 0.05) {
		sprite->SetFrame(0);
	}
	damageTimer.Update(dt);

}

void Alien::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet && !bullet->targetedAtPlayer) {
		hp -= BULLET_DAMAGE;
		Sprite* sprite = ((Sprite*)associated.GetComponent("Sprite"));
		sprite->SetFrame(1);
		damageTimer.Restart();
	}
}

void Alien::Render() {}

bool Alien::Is(std::string type) {
	return type == "Alien";
}
