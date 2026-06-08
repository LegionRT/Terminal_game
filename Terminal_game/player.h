#pragma once
#include "entity.h"
#include "location.h"
#include "inventory.h"
#include <memory>

class Weapon;

class Player : public Entity {
private:
	std::shared_ptr<Location> currentLocation;
	Inventory inventory;
	Weapon* equipped_weapon = nullptr;
public:
	Player(std::shared_ptr<Location> startLocation);
	~Player() = default;
	bool victory = false;
	void play();

	Inventory& get_inventory() { return inventory; }
	const Inventory& get_inventory() const { return inventory; }

	bool use_potion();
	void show_stats();
	int getDamage() const;
	void equip_best_weapon();
	bool equip_weapon_by_index(int index);

		int get_current_location_id() const { return currentLocation ? currentLocation->getId() : 1; }
	const Location* get_current_location() const { return currentLocation.get(); }
	void set_location(std::shared_ptr<Location> loc) { currentLocation = loc; }
	void setHealth(int hp) { getHealthRef() = hp; }
};