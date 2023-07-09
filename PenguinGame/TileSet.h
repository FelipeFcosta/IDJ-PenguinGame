#pragma once
#ifndef TILESET_H
#define TILESET_H
#include <string>
#include "Sprite.h"

// store tiles to render in the tileMap
class TileSet
{
public:
	TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);
	void RenderTile(unsigned index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();

private:
	Sprite tileSet;

	int rows, columns;
	int tileWidth, tileHeight;
};

#endif // TILESET_H