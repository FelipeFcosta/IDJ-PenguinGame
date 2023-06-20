#include "TileMap.h"
#include "Camera.h"
#include <iostream>

typedef long long ll;

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated), tileSet(tileSet) {
	Load(file);
}

TileMap::~TileMap() {
}

void TileMap::Load(std::string file) {
	std::fstream txtMap;

	txtMap.open(file, std::ios::in);

	if (txtMap.is_open()) {
		char separator;
		txtMap >> mapWidth >> separator;
		txtMap >> mapHeight >> separator;
		txtMap >> mapDepth >> separator;
		int tileIdx;
		while (txtMap >> tileIdx >> separator) {
			tileIdx -= 1;
			tileMatrix.emplace_back(tileIdx);
		}
	} else {
		std::cout << "Error while opening " << file << std::endl;
	}
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	return tileMatrix.at(CoordToIndex(x, y, z));
}

void TileMap::Render() {
	for (int layer = 0; layer < mapDepth; layer++) {
		RenderLayer(layer, Camera::pos.x, Camera::pos.y);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int numTiles = mapWidth;
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			if (At(x, y, layer) != -1) {
				float parallaxFactor = (layer == 0) ? 1 : 1.4;
				float xRenderPos = x * tileSet->GetTileWidth() - cameraX * parallaxFactor;
				float yRenderPos = y * tileSet->GetTileHeight() - cameraY * parallaxFactor;

				tileSet->RenderTile(At(x, y, layer), xRenderPos, yRenderPos);
			}
		}
	}
}

int TileMap::getWidth() {
	return mapWidth;
}

int TileMap::getHeight() {
	return mapHeight;
}

int TileMap::getDepth() {
	return mapDepth;
}

void TileMap::Update(float dt) {}

bool TileMap::Is(std::string type) {
	return type == "TileMap";
}

int TileMap::CoordToIndex(int x, int y, int z) {
	return x + y * mapWidth + z * mapWidth * mapHeight;
}
