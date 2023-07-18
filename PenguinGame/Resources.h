#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_TTF.h"
#include <string>
#include <memory>
#include <unordered_map>

class Resources
{
public:
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static void ClearImages();

	static std::shared_ptr<Mix_Music> GetMusic(std::string file);
	static void ClearMusics();

	static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
	static void ClearSounds();

	static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
	static void ClearFonts();

	template <typename T>
	static void ClearTable(std::unordered_map<std::string, std::shared_ptr<T>>);

	static void ClearAll();

private:
	// keep assets in a unordered_map structure to avoid relocating the same asset
	// <filename, asset>
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

};


#endif // RESOURCES_H

