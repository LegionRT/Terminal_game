#include "npc.h"
#include "player.h"
#include "location.h"
#include "potion.h"
#include "weapon.h"
#include "logger.h"
#include <iostream>

Npc::Npc(int id, const std::string& name, int hp, int dmg,
	NpcDisposition disp, DialogTree tree)
	: Entity(name, hp, dmg), npcId(id), disposition(disp), dialog(std::move(tree))
{
}

void Npc::turn_hostile() {
	disposition = NpcDisposition::Hostile;
	std::cout << getName() << " is now hostile!\n";
	Logger::instance().log(std::string("NPC turned hostile: ") + getName());
}

void Npc::applyOutcome(const DialogOutcome& outcome, Player& player, Location& location) {
	if (outcome.givePotion) {
		player.get_inventory().add_item(new Potion(outcome.potionName, outcome.potionHeal));
		std::cout << getName() << " gave you " << outcome.potionName << ".\n";
	}
	if (outcome.giveWeapon) {
		player.get_inventory().add_item(new Weapon(outcome.weaponName, outcome.weaponBonus));
		std::cout << getName() << " gave you " << outcome.weaponName << ".\n";
		player.equip_best_weapon();
	}
	if (outcome.unlockDoor) {
		auto& doors = location.getMap().getDoors();
		for (auto& d : doors) {
			if (d.isLocked()) {
				d.unlock();
				location.getMap().setTile(d.getX(), d.getY(), TileType::Door);
				std::cout << "A locked door was opened!\n";
				Logger::instance().log("NPC unlocked a door");
				break;
			}
		}
	}
	if (outcome.turnHostile) {
		turn_hostile();
	}
}

void Npc::interact(Player& player, Location& location) {
	if (is_hostile()) {
		std::cout << getName() << " wants to fight, not talk.\n";
		return;
	}

	std::cout << "\n--- Dialog with " << getName() << " ---\n";
	Logger::instance().log(std::string("Dialog started with NPC: ") + getName());

		dialog.run([&](const DialogOutcome& outcome) {
		applyOutcome(outcome, player, location);
		});

	Logger::instance().log(std::string("Dialog finished with NPC: ") + getName());
}