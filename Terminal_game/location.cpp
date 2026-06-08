#include "location.h"
#include "location_factory.h"
#include "logger.h"
#include "combat_system.h"
#include "player.h"
#include "weapon.h"
#include "npc.h"
#include <iostream>
#include <limits>

Location::Location(int id)
	: locationId(id),
	locationName(Map::getLocationNameById(id)),
	map(id)
{
}

void Location::addDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum)
{
	map.addOrUpdateDoorAt(x, y, targetId, isLocked, puzzleNum);
}

bool Location::unlockDoorToLocation(int sourceId, int matchX, int matchY)
{
	auto& doors = map.getDoors();

	if (matchX >= 0 && matchY >= 0)
	{
		for (auto& d : doors)
		{
			if (d.getX() == matchX && d.getY() == matchY && d.getTargetLocationId() == sourceId)
			{
				if (d.isLocked())
				{
					d.unlock();
					map.setTile(d.getX(), d.getY(), TileType::Door);
				}
				return true;
			}
		}
	}

	for (auto& d : doors)
	{
		if (d.getTargetLocationId() == sourceId)
		{
			if (d.isLocked())
			{
				d.unlock();
				map.setTile(d.getX(), d.getY(), TileType::Door);
			}
			return true;
		}
	}

	return false;
}

void Location::init()
{
	std::cout << "You entered " << locationName << "!" << std::endl;
	if (locationId == 5) {
		std::cout << "*** You reached the final chamber - you escaped the labyrinth! ***\n";
	}
	map.draw();

	Logger::instance().log(std::string("Entered location ") + std::to_string(locationId));
}

int Location::getId() const
{
	return locationId;
}

std::vector<std::string> Location::getActions(Player& player)
{
	std::vector<std::string> actions;

	auto& doors = map.getDoors();
	for (size_t i = 0; i < doors.size(); ++i)
	{
		const Door& d = doors[i];
		std::string state = d.isLocked() ? "(locked)" : "(open)";
		actions.emplace_back("Door " + std::to_string(i + 1) + " " + state
			+ " -> location " + std::to_string(d.getTargetLocationId())
			+ " (" + std::to_string(d.getX()) + "," + std::to_string(d.getY()) + ")");
	}

	for (const auto& spawn : map.getEnemies())
	{
		if (!spawn.alive || !spawn.enemy) continue;
		actions.emplace_back("Fight " + spawn.enemy->getName()
			+ " (HP: " + std::to_string(spawn.enemy->getHealth()) + ")");
	}

	for (const auto& spawn : map.getChests())
	{
		if (spawn.chest.is_empty()) continue;
		std::string state = spawn.chest.is_opened() ? "(open)" : "(closed)";
		actions.emplace_back("Chest " + state + " (" + std::to_string(spawn.x)
			+ "," + std::to_string(spawn.y) + ")");
	}

	for (const auto& spawn : map.getNpcs())
	{
		if (!spawn.active || !spawn.npc) continue;
		if (spawn.npc->is_friendly() && spawn.npc->has_dialog_left()) {
			actions.emplace_back("Talk to " + spawn.npc->getName());
		} else if (spawn.npc->is_alive()) {
			actions.emplace_back("Fight " + spawn.npc->getName()
				+ " (HP: " + std::to_string(spawn.npc->getHealth()) + ")");
		}
	}

	actions.emplace_back("Inventory (HP: " + std::to_string(player.getHealth())
		+ ", damage: " + std::to_string(player.getDamage()) + ")");
	actions.emplace_back("Exit game");
	return actions;
}

int Location::handleDoorAction(int doorIndex, Player& player)
{
	auto& doors = map.getDoors();
	if (doorIndex < 0 || doorIndex >= static_cast<int>(doors.size()))
	{
		std::cout << "Invalid door choice.\n";
		return -1;
	}

	Door& d = doors[doorIndex];
	int target = d.getTargetLocationId();
	if (target < 0)
	{
		std::cout << "This door leads nowhere.\n";
		return -1;
	}

	if (!d.isLocked())
	{
		std::cout << "Door is open. Moving to location " << target << "...\n";

		if (target >= 0)
		{
			auto targetLoc = LocationFactory::get(target);
			int oppX = d.getX();
			int oppY = d.getY();
			if (d.getX() == 0) oppX = Map::getWidth() - 1;
			else if (d.getX() == Map::getWidth() - 1) oppX = 0;
			if (d.getY() == 0) oppY = Map::getHeight() - 1;
			else if (d.getY() == Map::getHeight() - 1) oppY = 0;

			if (!targetLoc->unlockDoorToLocation(locationId, oppX, oppY))
			{
				targetLoc->addDoorAt(oppX, oppY, locationId, false, locationId % 3 + 1);
			}
		}

		return target;
	}

	bool nowOpen = d.interact(player);
	if (nowOpen)
	{
		map.setTile(d.getX(), d.getY(), TileType::Door);

		if (target >= 0)
		{
			auto targetLoc = LocationFactory::get(target);
			if (!targetLoc->unlockDoorToLocation(locationId))
			{
				int oppX = d.getX();
				int oppY = d.getY();
				if (d.getX() == 0) oppX = Map::getWidth() - 1;
				else if (d.getX() == Map::getWidth() - 1) oppX = 0;
				if (d.getY() == 0) oppY = Map::getHeight() - 1;
				else if (d.getY() == Map::getHeight() - 1) oppY = 0;

				targetLoc->addDoorAt(oppX, oppY, locationId, false, locationId % 3 + 1);
			}
		}

		return target;
	}

	return -1;
}

int Location::handleInventoryMenu(Player& player)
{
	while (true)
	{
		player.show_stats();

		auto& weapons = player.get_inventory().get_weapons();

		std::cout << "\n--- Inventory menu ---\n";
		std::cout << "1. Equip best weapon\n";
		std::cout << "2. Use potion\n";
		if (!weapons.empty()) {
			std::cout << "3. Equip weapon by number\n";
		}
		std::cout << "0. Back\n";
		std::cout << "Choice: ";

		int choice = 0;
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		switch (choice) {
		case 0:
			return -1;
		case 1:
			player.equip_best_weapon();
			break;
		case 2:
			if (!player.use_potion()) {
				std::cout << "No potions.\n";
			}
			break;
		case 3:
			if (!weapons.empty()) {
				std::cout << "Weapon number: ";
				int wChoice = 0;
				if (std::cin >> wChoice) {
					if (!player.equip_weapon_by_index(wChoice)) {
						std::cout << "Invalid number.\n";
					}
				}
			}
			break;
		default:
			std::cout << "Invalid choice.\n";
			break;
		}
	}
}

int Location::handleAction(int choice, Player& player)
{
	auto actions = getActions(player);
	if (choice < 1 || choice > static_cast<int>(actions.size()))
	{
		std::cout << "Invalid choice.\n";
		return -1;
	}

	auto& doors = map.getDoors();
	auto& enemies = map.getEnemies();
	auto& chests = map.getChests();
	auto& npcs = map.getNpcs();

	size_t index = 0;

	if (choice >= 1 && choice <= static_cast<int>(doors.size()))
	{
		return handleDoorAction(choice - 1, player);
	}
	index += doors.size();

	std::vector<size_t> aliveEnemyIndices;
	for (size_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i].alive) aliveEnemyIndices.push_back(i);
	}
	if (choice > static_cast<int>(index) && choice <= static_cast<int>(index + aliveEnemyIndices.size())) {
		size_t enemySlot = static_cast<size_t>(choice - index - 1);
		size_t enemyIdx = aliveEnemyIndices[enemySlot];
		MapEnemySpawn& spawn = enemies[enemyIdx];
		if (!spawn.enemy) return -1;
		CombatSystem combat(player, *spawn.enemy);
		bool won = combat.startBattle();
		if (!player.is_alive()) {
			return -3;
		}
		if (won) {
			spawn.alive = false;
			spawn.enemy->drop_loot(player.get_inventory());
			player.equip_best_weapon();
			if (spawn.enemy->isBoss()) {
				return -4;
			}
		}
	}
	index += aliveEnemyIndices.size(); 

			std::vector<size_t> availableChestIndices;
			for (size_t i = 0; i < chests.size(); ++i) {
				if (!chests[i].chest.is_empty()) availableChestIndices.push_back(i);
			}
			if (choice > static_cast<int>(index) && choice <= static_cast<int>(index + availableChestIndices.size()))
			{
				size_t chestSlot = static_cast<size_t>(choice - index - 1);
				size_t chestIdx = availableChestIndices[chestSlot];
				chests[chestIdx].chest.interact(player.get_inventory());
				player.equip_best_weapon();
				return -1;
			}
			index += availableChestIndices.size();

			std::vector<size_t> activeNpcIndices;
			for (size_t i = 0; i < npcs.size(); ++i) {
				if (!npcs[i].active || !npcs[i].npc || !npcs[i].npc->is_alive()) continue;
				if (npcs[i].npc->is_friendly() && npcs[i].npc->has_dialog_left()) {
					activeNpcIndices.push_back(i);
				}
				else if (npcs[i].npc->is_hostile()) {
					activeNpcIndices.push_back(i);
				}
			}
			if (choice > static_cast<int>(index) && choice <= static_cast<int>(index + activeNpcIndices.size()))
			{
				size_t npcSlot = static_cast<size_t>(choice - index - 1);
				size_t npcIdx = activeNpcIndices[npcSlot];
				MapNpcSpawn& spawn = npcs[npcIdx];

				if (!spawn.npc) return -1;

				if (spawn.npc->is_friendly() && spawn.npc->has_dialog_left()) {
					spawn.npc->interact(player, *this);
				}
				else {
					CombatSystem combat(player, *spawn.npc);
					bool won = combat.startBattle();
					if (!player.is_alive()) return -3;
					if (won) spawn.active = false;
				}
				return -1;
			}
			index += activeNpcIndices.size();

			if (choice == static_cast<int>(index + 1))
			{
				return handleInventoryMenu(player);
			}

			if (choice == static_cast<int>(index + 2))
			{
				return -2;
			}

			std::cout << "Invalid choice.\n";
			return -1;
		}
