#include "save_manager.h"
#include "player.h"
#include "location_factory.h"
#include "potion.h"
#include "weapon.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool SaveManager::save_game(const Player& player, const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) return false;

	file << "HP:" << player.getHealth() << "\n";
	file << "Location:" << player.get_current_location_id() << "\n";

	auto weapons = player.get_inventory().get_weapons();
	for (const auto* w : weapons) {
		file << "Weapon:" << w->get_name() << ":" << w->get_damage_bonus() << "\n";
	}

	auto potions = player.get_inventory().get_potions();
	for (const auto* p : potions) {
		file << "Potion:" << p->get_name() << ":" << p->get_heal_amout() << "\n";
	}

	const Location* loc = player.get_current_location();
	if (loc) {
		loc->getMap().save_state(file); 	}

	file.close();
	return true;
}

bool SaveManager::load_game(Player& player, const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	std::string line;
	int hp = 100;
	int targetLocationId = 1;
	std::vector<std::pair<std::string, int>> savedWeapons;
	std::vector<std::pair<std::string, int>> savedPotions;
	bool mapStateFound = false;

	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') line.pop_back(); 
		if (line.find("HP:") == 0) hp = std::stoi(line.substr(3));
		else if (line.find("Location:") == 0) targetLocationId = std::stoi(line.substr(9));
		else if (line.find("Weapon:") == 0) {
			std::string rest = line.substr(7);
			size_t pos = rest.rfind(':');
			if (pos != std::string::npos) savedWeapons.push_back({ rest.substr(0, pos), std::stoi(rest.substr(pos + 1)) });
		}
		else if (line.find("Potion:") == 0) {
			std::string rest = line.substr(7);
			size_t pos = rest.rfind(':');
			if (pos != std::string::npos) savedPotions.push_back({ rest.substr(0, pos), std::stoi(rest.substr(pos + 1)) });
		}
		else if (line == "MapStateStart") {
			mapStateFound = true;
			break;
		}
	}

		auto newLoc = LocationFactory::get(targetLocationId);
	player.set_location(newLoc);
	player.setHealth(hp);
	player.get_inventory().clear(); 
	for (const auto& w : savedWeapons) {
		player.get_inventory().add_item_silent(new Weapon(w.first, w.second));
	}
	for (const auto& p : savedPotions) {
		player.get_inventory().add_item_silent(new Potion(p.first, p.second));
	}
	player.equip_best_weapon();

	if (mapStateFound) {
		newLoc->getMap().load_state(file); 	}

	file.close();
	return true;
}