#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map() {
}

Map::~Map() {
}

void Map::loadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; ) {
		for (int x = 0; ; ) {
			mapFile.get(tile);
			if (tile == '0' || tile == '1' || tile == '2') {
				Game::addTile(atoi(&tile), x * 32, y * 32);
				x++;
			}
			if (tile == '\n') {
				y++;
				break;
			}
		}
	}

	mapFile.close();
}


