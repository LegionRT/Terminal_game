#include "player.h"
#include "weapon.h"
#include <iostream>
#include <limits>
#include "location_factory.h"
#include "logger.h"
#include "platform.h"

Player::Player(std::shared_ptr<Location> startLocation)
	: Entity("Player", 100, 1), currentLocation(std::move(startLocation))
{
}

bool Player::use_potion()
{
	auto potions = inventory.get_potions();
	if (potions.empty()) return false;
	Potion* p = potions[0];
	if (!p) return false;
	heal(p->get_heal_amout());
	std::cout << "You used " << p->get_name()
		<< " and restored " << p->get_heal_amout() << " HP." << std::endl;
	inventory.remove_item(p->get_id());
	return true;
}

void Player::show_stats()
{
	std::cout << "\n--- Player stats ---" << std::endl;
	std::cout << "Name: " << getName() << std::endl;
	std::cout << "HP: " << getHealth() << std::endl;
	std::cout << "Damage: " << getDamage() << std::endl;
	if (equipped_weapon) {
		std::cout << "Weapon: " << equipped_weapon->get_name()
			<< " (+" << equipped_weapon->get_damage_bonus() << ")" << std::endl;
	}
	else {
		std::cout << "Weapon: none" << std::endl;
	}
	inventory.show_items();
}

int Player::getDamage() const
{
	int dmg = Entity::getDamage();
	if (equipped_weapon) {
		dmg += equipped_weapon->get_damage_bonus();
	}
	return dmg;
}

void Player::equip_best_weapon()
{
	auto weapons = inventory.get_weapons();
	if (weapons.empty()) return;
	Weapon* best = weapons[0];
	for (Weapon* w : weapons) {
		if (w->get_damage_bonus() > best->get_damage_bonus()) {
			best = w;
		}
	}
	equipped_weapon = best;
	std::cout << "Equipped: " << best->get_name()
		<< " (+" << best->get_damage_bonus() << " damage)" << std::endl;
}

bool Player::equip_weapon_by_index(int index)
{
	auto weapons = inventory.get_weapons();
	if (index < 1 || index > static_cast<int>(weapons.size())) {
		return false;
	}
	equipped_weapon = weapons[static_cast<size_t>(index - 1)];
	std::cout << "Equipped: " << equipped_weapon->get_name()
		<< " (+" << equipped_weapon->get_damage_bonus() << " damage)" << std::endl;
	return true;
}

void Player::play()
{
	bool isRunning = true;
	while (isRunning)
	{
		clearScreen();

		currentLocation->init();
		auto actions = currentLocation->getActions(*this);
		std::cout << "\n--- Available actions ---\n";
		for (size_t i = 0; i < actions.size(); ++i)
		{
			std::cout << (i + 1) << ". " << actions[i] << "\n";
		}
		std::cout << "Your choice: ";
		int choice;
		if (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input error.\n";
			waitForEnter();
			continue;
		}

		int nextLocationId = currentLocation->handleAction(choice, *this);
		Logger::instance().log(
			std::string("Player selected action ") + std::to_string(choice)
			+ " in location " + std::to_string(currentLocation->getId())
		);

		if (nextLocationId == -3)
		{
			std::cout << "Game over.\n";
			Logger::instance().log("Player died");
			isRunning = false;
			break;
		}
		else if (nextLocationId == -2)
		{
			std::cout << "Thanks for playing!\n";
			Logger::instance().log("Player exited game");
			isRunning = false;
			break;
		}
		else if (nextLocationId == -4)
		{
			clearScreen();
			std::cout << R"(

=========================================
 ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗
 ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║
  ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║
   ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║
    ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║
    ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝

        FINAL BOSS DEFEATED

=========================================

)";
			std::cout << "\nYou completed the game!\n";
			isRunning = false;
			break;
		}
		else if (nextLocationId >= 0)
		{
			std::cout << "\nMoving to location " << nextLocationId << "...\n";
			Logger::instance().log("Transition to location " + std::to_string(nextLocationId));
			waitForEnter();
			currentLocation = LocationFactory::get(nextLocationId);
		}
		else
		{
			waitForEnter();
		}
	}
}