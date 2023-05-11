#include "Music.h"
#include "Resources.h"
#include <iostream>

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) {
	Open(file);
}

Music::~Music() {
	Stop(1500);
}

void Music::Play(int times) {
	if (Mix_PlayMusic(music, times) == -1) {
		std::cout << "error playing music: " << SDL_GetError();
	}
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file.c_str());
}

bool Music::IsOpen() {
	return music != nullptr;
}
