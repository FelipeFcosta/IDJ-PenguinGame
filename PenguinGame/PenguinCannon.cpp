#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include <iostream>

#define MINION_SPEED  (.15f) * 2.0f * (float) M_PI
#define MINION_RADIUS 200
#define BULLET_SPEED  350
#define BULLET_DAMAGE 10
#define BULLET_MAX_DIST 500
#define CANNON_COOLDOWN 0.3f

Timer timerCooldown;

PenguinCannon::~PenguinCannon() {}

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) :
        Component(associated), pbody(penguinBody), angle(0) {
    Sprite* pCannonSprite = new Sprite(associated, "resources/img/cubngun.png");
    Collider* pCannonCollider = new Collider(associated);

    associated.AddComponent(pCannonSprite);
    associated.AddComponent(pCannonCollider);

    timerCooldown = Timer();
}


void PenguinCannon::Update(float dt) {
    if (auto pbodyPtr = pbody.lock()) {
        timerCooldown.Update(dt);

        associated.box.x = pbodyPtr->box.GetCenter().x - associated.box.w/2;
        associated.box.y = pbodyPtr->box.GetCenter().y - associated.box.h/2;
        
        InputManager &input = InputManager::GetInstance();
        
        Vec2 mousePos = { (float) input.GetMouseX(), (float) input.GetMouseY() };
        Vec2 associatedCenter = associated.box.GetCenter();

        // angle between cannon and mouse position
        angle = Vec2::Angle({ 1, 0 }, mousePos - associatedCenter);
        ((Sprite*)associated.GetComponent("Sprite"))->SetAngleDeg(angle * 180.0f / (float)M_PI);

        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            if (timerCooldown.Get() >= CANNON_COOLDOWN) {
                Shoot();
                timerCooldown.Restart();
            }
        }
    } else {
        associated.RequestDelete();
    }
}

void PenguinCannon::Shoot() {

    GameObject* bulletObj = new GameObject();

    Bullet* bullet = new Bullet(*bulletObj, 4, 0.3, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DIST, "resources/img/penguinbullet.png", false);
    bulletObj->AddComponent(bullet);

    Vec2 cannonCenter = { associated.box.GetCenter().x - bulletObj->box.w/2, associated.box.GetCenter().y - bulletObj->box.h/2 };
    Vec2 cannonTip = { cannonCenter.x + associated.box.w/2, cannonCenter.y };
    cannonTip = cannonCenter + Vec2::Rotate((cannonTip - cannonCenter), angle);

    bulletObj->box.x = cannonTip.x;
    bulletObj->box.y = cannonTip.y;

    Sprite* bulletSprite = (Sprite*)bulletObj->GetComponent("Sprite");
    bulletSprite->SetAngleDeg(angle * 180.0f / (float)M_PI);

    Game::GetInstance().GetCurrentState().AddObject(bulletObj);
}

void PenguinCannon::NotifyCollision(GameObject& other) {
    //std::cout << "PenguinCannon collided!" << std::endl;
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}

