#pragma once
#include "inventory.h"

class Player;

class Chest {
private:
	Inventory contents;
	bool opened = false;
	bool is_locked = false;
	int puzzle_number = 0;

public:
	Chest() = default;
	void generate_loot(int mapId);

		void set_locked(int puzzleNum) { is_locked = true; puzzle_number = puzzleNum; }
	bool is_opened() const { return opened; }
	void set_opened(bool val) { opened = val; }
	bool is_empty() const;
	void clear_contents();

	void interact(Player& player);
};