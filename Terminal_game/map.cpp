#include "map.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <array>
#include <vector>

int Map::getId() const {
	return mapId;
}

TileType Map::getTile(int x, int y) const
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return TileType::Wall;
	return tiles[y][x];
}

void Map::setTile(int x, int y, TileType type)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	tiles[y][x] = type;
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

    // куда ведут двери; не допускаем отрицательных id
	int backId = (mapId > 1) ? mapId - 1 : -1;
	int forwardId = (mapId < 5) ? mapId + 1 : -1; // верхняя граница 5 (как было в коде)

	// Соберём список существующих целей (чтобы не получать отрицательные id)
	std::vector<int> targets;
	if (backId >= 0) targets.push_back(backId);
	if (forwardId >= 0) targets.push_back(forwardId);

	int doorCount = static_cast<int>(targets.size());

	// Очистим список дверей и заполнить их в соответствии с тайлами
	doors.clear();

	for (int i = 0; i < doorCount; i++)
	{
		int x = 0;
		int y = 0;

		// логика направления
		int targetId = targets[i];

		switch (sides[i])
		{
		case 0: x = WIDTH / 2;     y = 0; break;
		case 1: x = WIDTH / 2;     y = HEIGHT - 1; break;
		case 2: x = 0;             y = HEIGHT / 2; break;
		case 3: x = WIDTH - 1;     y = HEIGHT / 2; break;
		}

		std::bernoulli_distribution randomise(0.5);
		bool isLocked = !randomise(g);
		tiles[y][x] = isLocked ? TileType::LockedDoor : TileType::Door;

		// Создаём объект двери с позиционированием и целевой локацией
		int puzzleNum = (targetId >= 0) ? (targetId % 3 + 1) : 0;
		doors.emplace_back(x, y, targetId, isLocked, puzzleNum);
	}
}

std::vector<Door>& Map::getDoors()
{
	return doors;
}

void Map::addOrUpdateDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;

	// Обновим тайл
	tiles[y][x] = isLocked ? TileType::LockedDoor : TileType::Door;

	// Попробуем найти существующую дверь в этих координатах
	for (auto &d : doors)
	{
		if (d.getX() == x && d.getY() == y)
		{
			// Обновим параметры
			d = Door(x, y, targetId, isLocked, puzzleNum);
			return;
		}
	}

	// Если не нашли — добавим новую
	doors.emplace_back(x, y, targetId, isLocked, puzzleNum);
}
void Map::draw() const
{
    // Показываем игрока в центре карты для наглядности
	const int playerX = WIDTH / 2;
	const int playerY = HEIGHT / 2;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
            if (x == playerX && y == playerY)
			{
				std::cout << "@"; // символ игрока
				continue;
			}
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
