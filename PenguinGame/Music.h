#pragma once
#ifndef MUSIC_H
#define MUSIC_H
#include "SDL.h"
#include "SDL_Mixer.h"
#include <string>
#include <memory>

class Music
{
public:
	Music();
	Music(std::string file);
	~Music();
	void Play(int times = -1);
	void Stop(int msToStop = 1500);
	void Open(std::string file);
	bool IsOpen();
private:
	std::shared_ptr<Mix_Music> music;
	std::string currFile;

};

#endif // MUSIC_H