#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr) {}

Sprite::Sprite(GameObject& associated, string file) : Component(associated), texture(nullptr) {
	Open(file);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Sprite::Open(string file) {
	if (IsOpen()) {
		texture = nullptr;
	}

	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (texture == nullptr) {
		cout << "Error loading" << file << ": " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	// set width and height of image
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
	SDL_Rect dstrect;
	dstrect.x = associated.box.x;
	dstrect.y = associated.box.y;
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
	return type.compare("Sprite") == 0;
}