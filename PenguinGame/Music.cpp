#include "Music.h"

Music::Music() {
	music = nullptr;
}

Music::Music(string file) {
	Open(file);
}

Music::~Music() {
	Stop(1500);
	Mix_FreeMusic(music);
}

void Music::Play(int times) {
	if (Mix_PlayMusic(music, times) == -1) {
		cout << "error playing music: " << SDL_GetError();
	}
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
	music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) {
		cout << "error loading music file " << file << ": " << SDL_GetError();
	}
}

bool Music::IsOpen() {
	return music != nullptr;
}
