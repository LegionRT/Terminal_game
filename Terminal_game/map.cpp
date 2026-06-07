#include "map.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <array>

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

	// стороны для дверей
	std::array<int, 4> sides = { 0, 1, 2, 3 };

	// перемешка сторон
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(sides.begin(), sides.end(), g);

	// куда ведут двери
	int backId = mapId - 1;
	int forwardId = mapId + 1;

	// количество дверей на локации
	int doorCount = (mapId == 1 || mapId == 5) ? 1 : 2;

	for (int i = 0; i < doorCount; i++)
	{
		int x = 0;
		int y = 0;

		// логика направления
		int targetId = (i == 0) ? backId : forwardId;

		switch (sides[i])
		{
		case 0: x = WIDTH / 2;     y = 0; break;
		case 1: x = WIDTH / 2;     y = HEIGHT - 1; break;
		case 2: x = 0;             y = HEIGHT / 2; break;
		case 3: x = WIDTH - 1;     y = HEIGHT / 2; break;
		}

		std::bernoulli_distribution randomise(0.5);
		tiles[y][x] = randomise(g) ? TileType::Door : TileType::LockedDoor;
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
