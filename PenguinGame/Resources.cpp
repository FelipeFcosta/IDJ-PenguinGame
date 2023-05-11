#include "Resources.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
	auto imageIt = imageTable.find(file);
	if (imageIt != imageTable.end()) {
		return imageIt->second;
	}

	SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (texture == nullptr) {
		std::cout << "Error trying to get image \"" << file << "\": " << SDL_GetError() << std::endl;
	} else {
		imageTable[file] = texture;
	}

	return texture;
}

void Resources::ClearImages() {
	for (auto it = imageTable.begin(); it != imageTable.end(); it++) {
		SDL_DestroyTexture(it->second);
	}

	imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
	auto musicIt = musicTable.find(file);
	if (musicIt != musicTable.end()) {
		return musicIt->second;
	}
	Mix_Music* music = Mix_LoadMUS(file.c_str());

	if (music == nullptr) {
		std::cout << "Error trying to get music \"" << file << "\": " << SDL_GetError() << std::endl;
	} else {
		musicTable[file] = music;
	}

	return music;
}

void Resources::ClearMusics() {
	for (auto it = musicTable.begin(); it != musicTable.end(); it++) {
		Mix_FreeMusic(it->second);
	}

	musicTable.clear();
}


Mix_Chunk* Resources::GetSound(std::string file) {
	auto soundIt = soundTable.find(file);
	if (soundIt != soundTable.end()) {
		return soundIt->second;
	}
	Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

	if (sound == nullptr) {
		std::cout << "Error trying to get sound \"" << file << "\": " << SDL_GetError() << std::endl;
	} else {
		soundTable[file] = sound;
	}

	return sound;
}

void Resources::ClearSounds() {
	for (auto it = soundTable.begin(); it != soundTable.end(); it++) {
		Mix_FreeChunk(it->second);
	}

	musicTable.clear();
}

