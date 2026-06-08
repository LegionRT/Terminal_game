#pragma once

#include <vector>
#include <memory>
#include "door.h"
#include "enemy.h"
#include "chest.h"
#include "npc.h"
#include <string>

enum class TileType
{
	Floor,
	Wall,
	Door,
	LockedDoor
};

struct MapEnemySpawn {
	int x = 0;
	int y = 0;
	std::unique_ptr<Enemy> enemy;
	bool alive = true;
};

struct MapChestSpawn {
	int x = 0;
	int y = 0;
	Chest chest;
};

struct MapNpcSpawn {
	int x = 0;
	int y = 0;
	std::unique_ptr<Npc> npc;
	bool active = true;
};

class Map
{
private:
	int mapId;
	std::string mapName;
	static constexpr int WIDTH = 20;
	static constexpr int HEIGHT = 10;

	TileType tiles[HEIGHT][WIDTH];
	std::vector<Door> doors;
	std::vector<MapEnemySpawn> enemies;
	std::vector<MapChestSpawn> chests;
	std::vector<MapNpcSpawn> npcs;

	void spawnEntities();

public:
	Map(int id);
	static std::string getLocationNameById(int id);
	int getId() const;
	const std::string& getName() const;

	void generate();
	void draw() const;

	std::vector<Door>& getDoors();
	std::vector<MapEnemySpawn>& getEnemies() { return enemies; }
	const std::vector<MapEnemySpawn>& getEnemies() const { return enemies; }
	std::vector<MapChestSpawn>& getChests() { return chests; }
	const std::vector<MapChestSpawn>& getChests() const { return chests; }
	std::vector<MapNpcSpawn>& getNpcs() { return npcs; }
	const std::vector<MapNpcSpawn>& getNpcs() const { return npcs; }

	TileType getTile(int x, int y) const;
	void setTile(int x, int y, TileType type);

	void addOrUpdateDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum);

	static int getWidth() { return WIDTH; }
	static int getHeight() { return HEIGHT; }
};
