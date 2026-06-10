#include "combat_system.h"
#include <iostream>
#include <limits>
#include <cstdlib>

BattleResult CombatSystem::playerTurn() {
	while (true) {
		std::cout << "\n--- Your turn ---\n";
		std::cout << "HP: " << player.getHealth() << " | Damage: " << player.getDamage() << "\n";
		std::cout << "Opponent " << opponent.getName() << " HP: " << opponent.getHealth() << "\n";
		std::cout << "1. Attack\n";
		std::cout << "2. Use potion\n";
		std::cout << "3. Show stats\n";
		std::cout << "4. Run away\n";
		std::cout << "Choice: ";

		int choice = 0;
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. You miss your turn.\n";
			return BattleResult::Victory;
		}

		switch (choice) {
		case 1: {
			int damage = player.getDamage();
			opponent.take_damage(damage);
			std::cout << "You deal " << damage << " damage. Opponent HP: " << opponent.getHealth() << "\n";
			return BattleResult::Victory;
		}
		case 2:
			if (!player.use_potion()) {
				std::cout << "No potions available.\n";
				continue;
			}
			return BattleResult::Victory;
		case 3:
			player.show_stats();
			continue;
		case 4: {
			std::cout << "Attempting to escape...\n";
			if (rand() % 2 == 0) {
				std::cout << "You managed to escape!\n";
				return BattleResult::Escaped;
			}
			else {
				std::cout << "Failed to escape! The opponent will attack.\n";
				return BattleResult::Victory;
			}
		}
		default:
			std::cout << "Invalid choice. You lose your turn.\n";
			return BattleResult::Victory;
		}
	}
}

void CombatSystem::enemyTurn() {
	if (!opponent.is_alive()) return;
	int damage = opponent.getDamage();
	player.take_damage(damage);
	std::cout << opponent.getName() << " attacks for " << damage
		<< " damage. Your HP: " << player.getHealth() << "\n";
}

BattleResult CombatSystem::startBattle() {
	std::cout << "\n=== BATTLE ===\n";
	std::cout << opponent.getName() << " attacks you!\n";

	while (player.is_alive() && opponent.is_alive()) {
		BattleResult result = playerTurn();

		if (result == BattleResult::Escaped) return BattleResult::Escaped;
		if (!player.is_alive()) return BattleResult::Defeat;
		if (!opponent.is_alive()) break;

		enemyTurn();
	}

	if (!player.is_alive()) {
		std::cout << "You were defeated...\n";
		return BattleResult::Defeat;
	}

	std::cout << "You defeated " << opponent.getName() << "!\n";
	return BattleResult::Victory;
}