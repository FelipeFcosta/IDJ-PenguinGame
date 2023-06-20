#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr), width(0), height(0), scale({1, 1}), angleDeg(0) {}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated), texture(nullptr), scale({1, 1}), angleDeg(0) {
	Open(file);
}

Sprite::~Sprite() {
	// SDL_DestroyTexture(texture);	// not destroying since we're now sharing resources between objects
}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);
	// get and set width and height of image
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);	// clip will encompass the whole image
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render() {
	Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y, associated.box.w, associated.box.h);
}

void Sprite::Render(int x, int y, int w, int h) {
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = w ? w : clipRect.w;
	dstrect.h = h ? h : clipRect.h;

	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, angleDeg, nullptr, SDL_FLIP_NONE);
}


int Sprite::GetHeight() {
	return height * scale.y;
}

int Sprite::GetWidth() {
	return width * scale.x;
}

bool Sprite::IsOpen() {
	return texture != nullptr;
}

void Sprite::SetScale(float scaleX, float scaleY) {
	scale.x = scaleX ? scaleX : scale.x;
	scale.y = scaleY ? scaleY : scale.y;

	associated.box.x -= (associated.box.w * scaleX - associated.box.w) / 2;
	associated.box.y -= (associated.box.h * scaleY - associated.box.h) / 2;

	associated.box.w *= scale.x;
	associated.box.h *= scale.y;
}

Vec2 Sprite::GetScale() {
	return scale;
}

void Sprite::SetAngleDeg(double angleDeg) {
	this->angleDeg = angleDeg;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type) {
	return type == "Sprite";
}