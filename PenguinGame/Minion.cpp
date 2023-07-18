#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include <iostream>

#define MINION_SPEED  (.15f) * 2.0f * (float) M_PI
#define MINION_RADIUS 200
#define BULLET_SPEED  300
#define BULLET_DAMAGE 10
#define BULLET_MAX_DIST 1000

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg, float speedFactor)
	: Component(associated), arc(arcOffsetDeg * (float) M_PI/180.0f), alienCenter(alienCenter), speedFactor(speedFactor) {

	Sprite* minionSprite = new Sprite(associated, "resources/img/minion.png", 2, 0);
	Collider* minionCollider = new Collider(associated, {0.5, 0.5});

	associated.AddComponent(minionSprite);
	associated.AddComponent(minionCollider);

	this->speedFactor = speedFactor;
	damageTimer = Timer();
}

void Minion::Shoot(Vec2 target) {
	Sprite* minionSprite = (Sprite*)associated.GetComponent("Sprite");

	if (minionSprite->IsVisible()) {

		Vec2 associatedCenter = associated.box.GetCenter();
		float angle = Vec2::Angle({ 1, 0 }, target - associated.box.GetCenter());

		GameObject* bulletObj = new GameObject();
		Bullet* bullet = new Bullet(*bulletObj, 3, 0.1, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DIST, "resources/img/minionbullet2.png", true);
		bulletObj->AddComponent(bullet);

		bulletObj->box.x = associatedCenter.x;
		bulletObj->box.y = associatedCenter.y;

		Sprite* bulletSprite = (Sprite*)bulletObj->GetComponent("Sprite");
		bulletSprite->SetAngleDeg(angle * 180.0f / (float)M_PI);

		Game::GetInstance().GetCurrentState().AddObject(bulletObj);
	}
}

void Minion::Update(float dt) {
	if (std::shared_ptr<GameObject> alienCenterPtr = alienCenter.lock()) {
		associated.box.x = alienCenterPtr->box.x + associated.box.w/2;
		associated.box.y = alienCenterPtr->box.y + associated.box.h/2;
	} else {
		associated.RequestDelete();
		return;
	}

	Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
	sprite->SetAngleDeg(arc*180.0f/3.1415f);

	Vec2 minionDistance({ MINION_RADIUS, 0 });
	Vec2 minionRotated = Vec2::Rotate(minionDistance, arc);

	associated.box.x += minionRotated.x;
	associated.box.y += minionRotated.y;
	
	// increment the arc in each frame
	arc += MINION_SPEED * speedFactor * dt;

	if (sprite->GetFrame() == 1 && damageTimer.Get() >= 0.05) {
		sprite->SetFrame(0);
	}
	damageTimer.Update(dt);
}

void Minion::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet && !bullet->targetedAtPlayer) {
		Sprite* sprite = ((Sprite*)associated.GetComponent("Sprite"));
		sprite->SetFrame(1);
		damageTimer.Restart();
	}
}

void Minion::Render() {}

bool Minion::Is(std::string type) {
	return type == "Minion";
}