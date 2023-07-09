#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include "Sound.h"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr),
		width(0), height(0), scale({1, 1}), angleDeg(0), frameCount(1), frameTime(1), currentFrame(0), timeElapsed(0) {
	clipRect.x = 0; clipRect.y = 0; clipRect.w = 0; clipRect.h = 0;
	secondsToSelfDestruct = 0;
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, Vec2 scale, float secondsToSelfDestruct) : Component(associated),
		texture(nullptr), scale({1, 1}), angleDeg(0), timeElapsed(0), currentFrame(0) {
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->secondsToSelfDestruct = secondsToSelfDestruct;

	Open(file);
	SetScale(scale.x, scale.y);
}

Sprite::~Sprite() {
	// SDL_DestroyTexture(texture);	// not destroying since we're now sharing resources between objects
}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);
	// get and set width and height of image
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	associated.box.w = GetWidth();
	associated.box.h = height;
	SetClip(0, 0, associated.box.w, height);
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
	return height;
}

int Sprite::GetWidth() {
	return ((float) width / (float) frameCount);
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

double Sprite::GetAngleDeg() {
	return angleDeg;
}


void Sprite::Update(float dt) {

	timeElapsed += dt;
	if (frameTime && timeElapsed > frameTime) {
		currentFrame += 1;
		timeElapsed = 0;
		SetClip(GetWidth() * (currentFrame % frameCount), clipRect.y, GetWidth(), GetHeight());
	}

	if (currentFrame >= frameCount) {
		currentFrame = 0;
	}

	// self destruction animation
	if (secondsToSelfDestruct > 0) {
		selfDestructCount.Update(dt);
		if (selfDestructCount.Get() >= secondsToSelfDestruct) {
			Sound* associatedSound = (Sound*)associated.GetComponent("Sound");
			if (associatedSound && associatedSound->IsPlaying()) {
				// stop animation but don't destroy associatedObj while playing sound
				frameTime = 0;
				clipRect.w = 0;
			} else {
				associated.RequestDelete();
			}
		}
	}
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
	timeElapsed = 0;
	SetClip(GetWidth() * (currentFrame % frameCount), clipRect.y, GetWidth(), GetHeight());
}

void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;
    associated.box.w = width / frameCount;
    currentFrame = 0;
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}

int Sprite::GetFrame() {
    return currentFrame;
}

int Sprite::GetFrameCount() {
    return frameCount;
}

float Sprite::GetFrameTime() {
	return frameTime;
}

bool Sprite::Is(std::string type) {
	return type == "Sprite";
}

