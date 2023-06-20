#include "TileSet.h"

// sets width and height of its tiles and opens associated Sprite
TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileWidth(tileWidth), tileHeight(tileHeight), tileSet(*(GameObject*) NULL) {
	tileSet.Open(file);

	if (tileSet.IsOpen()) {
		rows = tileSet.GetHeight() / tileHeight;
		columns = tileSet.GetWidth() / tileWidth;
	} else {
		rows = NULL;
		columns = NULL;
	}
}

// render tile(with specified index position) to the screen at(x, y)
void TileSet::RenderTile(unsigned index, float x, float y) {
	int numTiles = rows * columns;
	if (index >= 0 && index <= numTiles-1) {
		int indexRow = index % columns;
		int indexColumn = index / columns;

		tileSet.SetClip(indexRow * tileWidth, indexColumn * tileHeight, tileWidth, tileHeight);
		tileSet.Render(x, y, tileWidth, tileHeight);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}


int TileSet::GetTileHeight() {
	return tileHeight;
}
