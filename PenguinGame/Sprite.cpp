#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr), width(0), height(0) {}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated), texture(nullptr) {
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
	Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y) {
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.h = clipRect.h;
	dstrect.w = clipRect.w;

	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}


int Sprite::GetHeight() {
	return height;
}

int Sprite::GetWidth() {
	return width;
}

bool Sprite::IsOpen() {
	return texture != nullptr;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type) {
	return type == "Sprite";
}