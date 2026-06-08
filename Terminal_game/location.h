#pragma once
#include "map.h"
#include <string>
#include <vector>

class Player;

class Location {
private:
	int locationId;
	std::string locationName;
	Map map;
	int handleInventoryMenu(Player& player);
	int handleDoorAction(int doorIndex, Player& player);
public:
	Location(int id);
	void init();
	int getId() const;
	std::vector<std::string> getActions(Player& player);
	int handleAction(int choice, Player& player);
	void addDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum);
	bool unlockDoorToLocation(int sourceId, int matchX = -1, int matchY = -1);

	Map& getMap() { return map; }
	const Map& getMap() const { return map; } };