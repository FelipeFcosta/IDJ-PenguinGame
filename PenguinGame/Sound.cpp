#include "Sound.h"
#include "Resources.h"
#include <iostream>

Sound::Sound(GameObject& associated) : Component(associated), chunk(nullptr), channel(-1) {}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
	Open(file);
}

Sound::~Sound() {
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
	}
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk, times - 1);
	if (channel == -1) {
		std::cout << "error playing sound: " << SDL_GetError();
	}
}

void Sound::Stop() {
	if (channel >= 0)
		Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
	return chunk != nullptr;
}

bool Sound::IsPlaying() {
	return Mix_Playing(channel);
}

void Sound::Update(float dt) {}
void Sound::Render() {}

bool Sound::Is(std::string type) {
	return type.compare("Sound") == 0;
}
