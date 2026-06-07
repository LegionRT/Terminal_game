#pragma once

#include <vector>
#include "door.h"
#include <string>

enum class TileType
{
	Floor,
	Wall,
	Door,
	LockedDoor
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

public:
	Map(int id);
	static std::string getLocationNameById(int id);
	int getId() const;
	const std::string& getName() const;

	void generate();
	void draw() const;

	TileType getTile(int x, int y) const;
	void setTile(int x, int y, TileType type);

	static int getWidth() { return WIDTH; }
	static int getHeight() { return HEIGHT; }
};