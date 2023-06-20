#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite)
	: Component(associated), speed({speed, 0}) {
	Sprite* bulletSprite = new Sprite(associated, sprite);
	associated.AddComponent(bulletSprite);

	this->speed = this->speed.GetRotated(angle);

	this->damage = damage;
	this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt) {
	distanceLeft -= Vec2::Magnitude(speed)*dt;
	if (distanceLeft > 0) {
		associated.box.x += speed.x * dt;
		associated.box.y += speed.y * dt;
	} else {
		associated.RequestDelete();
	}

}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
	return type == "Bullet";
}

int Bullet::GetDamage() {
	return damage;
}
