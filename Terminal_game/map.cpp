#include "map.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <random>

int Map::getId() const {
	return mapId;
}

const std::string& Map::getName() const {
	return mapName;
}

std::string Map::getLocationNameById(int id) {
	return "Локацию номер " + std::to_string(id);
}
Map::Map(int id) : mapId(id), mapName(getLocationNameById(id))
{
	generate();
}
void Map::generate()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			tiles[y][x] =
				(x == 0 || x == WIDTH - 1 ||
					y == 0 || y == HEIGHT - 1)
				? TileType::Wall
				: TileType::Floor;
		}
	}
}
void Map::draw() const
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			switch (tiles[y][x])
			{
			case TileType::Floor:
				std::cout << ".";
				break;
			case TileType::Wall:
				std::cout << "#";
				break;
			case TileType::Door:
				std::cout << "D";
				break;
			case TileType::LockedDoor:
				std::cout << "L";
				break;
			}
		}
		std::cout << std::endl;
	}
}
