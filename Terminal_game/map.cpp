#include "map.h"
#include "dialog.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <array>
#include <vector>
#include <utility>

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
	return "Location " + std::to_string(id);
}

Map::Map(int id) : mapId(id), mapName(getLocationNameById(id))
{
	generate();
}

void Map::spawnEntities()
{
	const int playerX = WIDTH / 2;
	const int playerY = HEIGHT / 2;

	std::vector<std::pair<int, int>> freeTiles;
	for (int y = 1; y < HEIGHT - 1; ++y) {
		for (int x = 1; x < WIDTH - 1; ++x) {
			if (tiles[y][x] != TileType::Floor)
				continue;
			if (x == playerX && y == playerY)
				continue;
			freeTiles.emplace_back(x, y);
		}
	}

	if (freeTiles.empty())
		return;

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(freeTiles.begin(), freeTiles.end(), g);

	static const char* enemyNames[] = { "Goblin", "Orc", "Skeleton", "Troll" };
	static const char* enemyBossNames[] = { "Dragon", "Demon", "Lich", "Giant" };
	int enemyCount = 1 + (mapId % 3);
	enemyCount = std::min(enemyCount, static_cast<int>(freeTiles.size()));

	enemies.clear();

	if (mapId == 5)
	{
		std::uniform_int_distribution<int> bossDist(0, 3);
		int bossIndex = bossDist(g);

		std::string bossName = enemyBossNames[bossIndex];

		MapEnemySpawn boss;
		boss.x = freeTiles[0].first;
		boss.y = freeTiles[0].second;

		boss.enemy = std::make_unique<Enemy>(
			bossName,
			1,
			25,
			"The final boss",
			true
		);

		boss.alive = true;
		enemies.push_back(std::move(boss));
	}
	else
	{
		for (int i = 0; i < enemyCount; ++i)
		{
			int x = freeTiles[i].first;
			int y = freeTiles[i].second;

			int hp = 10 + mapId * 5 + i * 3;
			int dmg = 2 + mapId + i;

			std::string name =
				std::string(enemyNames[i % 4]) +
				" #" +
				std::to_string(i + 1);

			MapEnemySpawn spawn;
			spawn.x = x;
			spawn.y = y;
			spawn.enemy = std::make_unique<Enemy>(name,hp,dmg,"A hostile creature");
			spawn.alive = true;

			enemies.push_back(std::move(spawn));
		}
	}

	npcs.clear();
	size_t tileIdx = static_cast<size_t>(enemyCount);

	if (tileIdx < freeTiles.size()) {
		MapChestSpawn chestSpawn;
		chestSpawn.x = freeTiles[tileIdx].first;
		chestSpawn.y = freeTiles[tileIdx].second;
		chestSpawn.chest.generate_loot(mapId);
		chests.push_back(std::move(chestSpawn));
		tileIdx++;
	}

	std::unique_ptr<Npc> npc;
	if (mapId == 1) {
		npc = std::make_unique<Npc>(1, "Hermit", 40, 4, NpcDisposition::Friendly,
			DialogTree::createHermitDialog());
	} else if (mapId == 3) {
		npc = std::make_unique<Npc>(2, "Merchant", 35, 5, NpcDisposition::Friendly,
			DialogTree::createMerchantDialog());
	}

	if (npc && tileIdx < freeTiles.size()) {
		MapNpcSpawn npcSpawn;
		npcSpawn.x = freeTiles[tileIdx].first;
		npcSpawn.y = freeTiles[tileIdx].second;
		npcSpawn.npc = std::move(npc);
		npcs.push_back(std::move(npcSpawn));
	}
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

	std::array<int, 4> sides = { 0, 1, 2, 3 };

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(sides.begin(), sides.end(), g);

	int backId = (mapId > 1) ? mapId - 1 : -1;
	int forwardId = (mapId < 5) ? mapId + 1 : -1;

	std::vector<int> targets;
	if (backId >= 0) targets.push_back(backId);
	if (forwardId >= 0) targets.push_back(forwardId);

	int doorCount = static_cast<int>(targets.size());

	doors.clear();
	chests.clear();

	for (int i = 0; i < doorCount; i++)
	{
		int x = 0;
		int y = 0;

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

		int puzzleNum = (targetId >= 0) ? (targetId % 3 + 1) : 0;
		doors.emplace_back(x, y, targetId, isLocked, puzzleNum);
	}

	spawnEntities();
}

std::vector<Door>& Map::getDoors()
{
	return doors;
}

void Map::addOrUpdateDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;

	tiles[y][x] = isLocked ? TileType::LockedDoor : TileType::Door;

	for (auto& d : doors)
	{
		if (d.getX() == x && d.getY() == y)
		{
			d = Door(x, y, targetId, isLocked, puzzleNum);
			return;
		}
	}

	doors.emplace_back(x, y, targetId, isLocked, puzzleNum);
}

void Map::draw() const
{
	const int playerX = WIDTH / 2;
	const int playerY = HEIGHT / 2;

	std::cout << "Legend: @ player, E enemy, N NPC, C chest, D door, L locked door\n";

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == playerX && y == playerY)
			{
				std::cout << "@";
				continue;
			}

			bool drawn = false;
			for (const auto& spawn : enemies) {
				if (spawn.alive && spawn.x == x && spawn.y == y) {
					std::cout << (spawn.enemy->isBoss() ? "B" : "E");
					drawn = true;
					break;
				}
			}
			if (drawn) continue;

			for (const auto& spawn : npcs) {
				if (spawn.active && spawn.npc && spawn.x == x && spawn.y == y) {
					std::cout << (spawn.npc->is_hostile() ? "!" : "N");
					drawn = true;
					break;
				}
			}
			if (drawn) continue;

			for (const auto& spawn : chests) {
				if (spawn.x == x && spawn.y == y && !spawn.chest.is_empty()) {
					std::cout << (spawn.chest.is_opened() ? "c" : "C");
					drawn = true;
					break;
				}
			}
			if (drawn) continue;

			for (const auto& spawn : chests) {
				if (spawn.x == x && spawn.y == y && !spawn.chest.is_empty()) {
					std::cout << (spawn.chest.is_opened() ? "c" : "C");
					drawn = true;
					break;
				}
			}
			if (drawn) continue;

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
