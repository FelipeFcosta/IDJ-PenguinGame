#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Sprite.h"
#include "Sound.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Minion.h"
#include "Alien.h"
#include "Camera.h"
#include "Timer.h"
#include "Game.h"
#include <iostream>

#define HP 1000
#define MAX_SPEED 300
#define MIN_SPEED 10
#define ANGULAR_SPEED 1.0f * 2.0f * (float) M_PI
#define ACCELERATION 250
#define BULLET_DAMAGE 0.1*HP
#define MINION_DAMAGE 0.01*HP
#define ALIEN_DAMAGE 0.02*HP

PenguinBody* PenguinBody::player;


PenguinBody::~PenguinBody() {
    player = nullptr;
}

PenguinBody::PenguinBody(GameObject& associated) : Component(associated),
    speed({ 0, 0 }), angle(0), hp(HP), linearSpeed(0), position({ associated.box.x, associated.box.y }) {
    Sprite* pBodySprite = new Sprite(associated, "resources/img/penguin.png", 2, 0);
    Collider* pBodyCollider = new Collider(associated);

    associated.AddComponent(pBodySprite);
    associated.AddComponent(pBodyCollider);
    damageTimer = Timer();
    endTimer = Timer();
    penguinDead = false;
    player = this;
}


void PenguinBody::Start() {
    GameObject* pCannonObj = new GameObject();
    PenguinCannon* pCannon = new PenguinCannon(*pCannonObj, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
    pCannonObj->AddComponent(pCannon);
    pcannon = Game::GetInstance().GetCurrentState().AddObject(pCannonObj);
}

void PenguinBody::Update(float dt) {
    InputManager &input = InputManager::GetInstance();
    if (input.IsKeyDown(W_KEY)) {
        if (linearSpeed < MAX_SPEED) {
            linearSpeed += ACCELERATION * dt;
        }
    } else if (input.IsKeyDown(S_KEY)) {
        if (linearSpeed > -MAX_SPEED) {
            linearSpeed -= ACCELERATION * dt;
        }
    } else {    // slow down
        if (abs(linearSpeed) > MIN_SPEED) {
            linearSpeed = linearSpeed + (linearSpeed > 0 ? -ACCELERATION : ACCELERATION) * dt;
        } else {
            linearSpeed = 0;
        }
    }
    if (input.IsKeyDown(A_KEY)) {
        angle -= ANGULAR_SPEED * dt;
    } else if (input.IsKeyDown(D_KEY)) {
        angle += ANGULAR_SPEED * dt;
    }

    Vec2 normalizedSpeed = Vec2::Rotate(Vec2({ 1, 0 }), angle);
    speed.x = normalizedSpeed.x * linearSpeed;
    speed.y = normalizedSpeed.y * linearSpeed;

    // border limits
    if (associated.box.x + associated.box.w/2 > 1408) {
        associated.box.x = 1408 - associated.box.w/2 - 1;
        speed.x = 0;
        linearSpeed = linearSpeed > 0 ? abs(speed.y) : -abs(speed.y);
    } else if (associated.box.x < 0) {
        associated.box.x = 1;
        speed.x = 0;
        linearSpeed = linearSpeed > 0 ? abs(speed.y) : -abs(speed.y);
    } else if (associated.box.y + associated.box.h/2 > 1280) {
        associated.box.y = 1280 - associated.box.h/2 - 1;
        speed.y = 0;
        linearSpeed = linearSpeed > 0 ? abs(speed.x) : -abs(speed.x);
    } else if (associated.box.y < 0) {
        associated.box.y = 1;
        speed.y = 0;
        linearSpeed = linearSpeed > 0 ? abs(speed.x) : -abs(speed.x);
    }

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    position = { associated.box.x, associated.box.y };


    Sprite* sprite = ((Sprite*)associated.GetComponent("Sprite"));
    sprite->SetAngleDeg(angle * 180.0f / (float)M_PI);

    if (hp <= 0) {
        if (!penguinDead) {
            penguinDead = true;
            endTimer.Restart();
            if (auto pCannon = pcannon.lock()) {
                pCannon->RequestDelete();
            }
            Camera::UnFollow();

            GameObject* deathObj = new GameObject();
            Sprite* deathSprite = new Sprite(*deathObj, "resources/img/penguindeath.png", 5, 0.25, { 1, 1 }, 5 * 0.25);
            deathObj->box.x = associated.box.x;
            deathObj->box.y = associated.box.y;
            deathObj->AddComponent(deathSprite);
            Sound* deathSound = new Sound(*deathObj, "resources/audio/boom.wav");
            deathSound->SetVolume(50);
            deathSound->Play(1);
            deathObj->AddComponent(deathSound);
            Game::GetInstance().GetCurrentState().AddObject(deathObj);

            // make previous sprite disappear
            ((Sprite*)associated.GetComponent("Sprite"))->SetVisible(false);
        }
    }

    if (sprite->GetFrame() == 1 && damageTimer.Get() >= 0.05) {
        sprite->SetFrame(0);
        Camera::shakeTime = 0;
    }
    damageTimer.Update(dt);
    endTimer.Update(dt);

    if (penguinDead && endTimer.Get() >= 5 * 0.25) {
        associated.RequestDelete();
        Camera::shakeTime = 0;
    }
}

void PenguinBody::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    Minion* minion = (Minion*)other.GetComponent("Minion");
    Alien* alien = (Alien*)other.GetComponent("Alien");
    if (bullet && bullet->targetedAtPlayer)
        hp -= BULLET_DAMAGE;
    if (minion)
        hp -= MINION_DAMAGE;
    if (alien)
        hp -= ALIEN_DAMAGE;

    if ((bullet && bullet->targetedAtPlayer) || alien || minion) {
        Camera::shakeTime = 0.5f;
        Sprite* sprite = ((Sprite*)associated.GetComponent("Sprite"));
        sprite->SetFrame(1);
        damageTimer.Restart();
    }

}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}
