#pragma once
#include "entity.h"
#include "location.h"
#include "inventory.h"
#include <memory>

class Weapon;

class Player : public Entity
{
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
	bool use_potion();
	void show_stats();
	int getDamage() const;
	void equip_best_weapon();
	bool equip_weapon_by_index(int index);
};
