#include "Resources.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;



std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
	auto imageIt = imageTable.find(file);
	if (imageIt != imageTable.end()) {
		return imageIt->second;
	}

	SDL_Texture* t = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (t != nullptr) {
		// custom deletion
		auto deleter = [](SDL_Texture* texture) {
			SDL_DestroyTexture(texture);
		};

		std::shared_ptr<SDL_Texture> texture(t, deleter);
		imageTable[file] = texture;
		return texture;
	} else {
		std::cout << "Error trying to get image \"" << file << "\": " << SDL_GetError() << std::endl;
		return nullptr;
	}
}

void Resources::ClearImages() {
	ClearTable(imageTable);
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
	auto musicIt = musicTable.find(file);
	if (musicIt != musicTable.end()) {
		return musicIt->second;
	}

	Mix_Music* m = Mix_LoadMUS(file.c_str());
	if (m != nullptr) {
		auto deleter = [](Mix_Music* music) {
			Mix_FreeMusic(music);
		};

		std::shared_ptr<Mix_Music> music(m, deleter);
		musicTable[file] = music;
		return music;
	}
	else {
		std::cout << "Error trying to get music \"" << file << "\": " << SDL_GetError() << std::endl;
		return nullptr;
	}
}

void Resources::ClearMusics() {
	ClearTable(musicTable);
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
	auto soundIt = soundTable.find(file);
	if (soundIt != soundTable.end()) {
		return soundIt->second;
	}
	
	Mix_Chunk* s = Mix_LoadWAV(file.c_str());
	if (s != nullptr) {
		auto deleter = [](Mix_Chunk* sound) {
			Mix_FreeChunk(sound);
		};

		std::shared_ptr<Mix_Chunk> sound(s, deleter);
		soundTable[file] = sound;
		return sound;
	}
	else {
		std::cout << "Error trying to get sound \"" << file << "\": " << SDL_GetError() << std::endl;
		return nullptr;
	}
}

void Resources::ClearSounds() {
	ClearTable(soundTable);
}


std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize) {
	std::string key = file + "_" + std::to_string(fontSize);

	auto fontIt = fontTable.find(key);
	if (fontIt != fontTable.end()) {
		return fontIt->second;
	}

	TTF_Font* f = TTF_OpenFont(file.c_str(), fontSize);
	if (f != nullptr) {
		auto deleter = [](TTF_Font* font) {
			TTF_CloseFont(font);
		};

		std::shared_ptr<TTF_Font> font(f, deleter);
		fontTable[key] = font;
		return font;
	}
	else {
		std::cout << "Error trying to get font \"" << file << "\": " << SDL_GetError() << std::endl;
		return nullptr;
	}
}

void Resources::ClearFonts() {
	ClearTable(fontTable);
}

template <typename T>
void Resources::ClearTable(std::unordered_map<std::string, std::shared_ptr<T>> table) {
	auto it = table.begin();
	while (it != table.end()) {
		if (it->second.unique()) {
			it = table.erase(it);
		}
		else {
			it++;
		}
	}
}


void Resources::ClearAll() {
	ClearImages();
	ClearMusics();
	ClearSounds();
	ClearFonts();
	ClearTable(fontTable);
}

