#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

#define MINION_SPEED  (.15f) * 2.0f * (float) M_PI
#define MINION_RADIUS 200
#define BULLET_SPEED  300
#define BULLET_DAMAGE 10
#define BULLET_MAX_DIST 800

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg)
	: Component(associated), arc(arcOffsetDeg * (float) M_PI /180.0f), alienCenter(alienCenter) {

	Sprite* minionSprite = new Sprite(associated, "resources/img/minion.png");
	associated.AddComponent(minionSprite);
	associated.box.w = minionSprite->GetWidth();
	associated.box.h = minionSprite->GetHeight();

}

void Minion::Render() {}

bool Minion::Is(std::string type) {
	return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
	Vec2 associatedCenter = { associated.box.x + associated.box.w/2, associated.box.y + associated.box.h/2 };
	float angle = Vec2::Angle({1, 0}, Vec2::Subtract(target, associatedCenter));

	GameObject* bulletObj = new GameObject();
	Bullet *bullet = new Bullet(*bulletObj, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DIST, "resources/img/minionbullet1.png");
	bulletObj->AddComponent(bullet);

	bulletObj->box.x = associatedCenter.x;
	bulletObj->box.y = associatedCenter.y;

	Sprite* bulletSprite = (Sprite*)bulletObj->GetComponent("Sprite");
	bulletSprite->SetAngleDeg(angle * 180.0f / (float) M_PI);

	Game::GetInstance().GetState().AddObject(bulletObj);
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
	Vec2 minionRotated = minionDistance.GetRotated(arc);

	associated.box.x += minionRotated.x;
	associated.box.y += minionRotated.y;
	
	// increment the arc in each frame
	arc += MINION_SPEED * dt;
}