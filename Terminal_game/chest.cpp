#include "chest.h"
#include "potion.h"
#include "weapon.h"
#include "player.h"
#include "math_puzzle.h"
#include "riddle_puzzle.h"
#include "lockpick_puzzle.h"
#include <iostream>
#include <memory>

void Chest::generate_loot(int mapId) {
	contents.add_item_silent(new Potion("Healing Potion", 8 + mapId * 2));
	contents.add_item_silent(new Potion("Minor Healing Potion", 5 + mapId));
	if (mapId % 2 == 0) {
		contents.add_item_silent(new Weapon("Rusty Dagger", 2 + mapId));
	}
	else {
		contents.add_item_silent(new Weapon("Iron Sword", 3 + mapId));
	}
}

bool Chest::is_empty() const {
	return contents.is_empty();
}

void Chest::clear_contents() {
	contents.clear(); }

void Chest::interact(Player& player) {
	if (is_empty()) {
		std::cout << "The chest is empty.\n";
		return;
	}

	if (is_locked) {
		std::cout << "This chest is locked and requires solving a puzzle!\n";
		std::unique_ptr<Puzzle> puzzle;
		switch (puzzle_number) {
		case 1: puzzle = std::make_unique<MathPuzzle>(); break;
		case 2: puzzle = std::make_unique<RiddlePuzzle>(); break;
		case 3: puzzle = std::make_unique<LockpickPuzzle>(); break;
		default: std::cout << "The lock is broken.\n"; return;
		}

		if (puzzle->play()) {
			is_locked = false;
			std::cout << "The lock clicked! The chest is open.\n";
		}
		else {
			std::cout << "You failed the puzzle. You take 3 damage from a trap!\n";
			player.take_damage(3);
			return;
		}
	}

	if (!opened) {
		std::cout << "You opened the chest!\n";
		opened = true;
	}

	std::cout << "Chest contents:\n";
	contents.show_items();
	contents.transfer_all_to(player.get_inventory());
	std::cout << "You took all items from the chest.\n";
}