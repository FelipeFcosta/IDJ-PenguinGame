#include "Face.h"
#include "Sound.h"
#include "Sprite.h"


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

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(std::string type) {
	return type.compare("Face") == 0;
}
