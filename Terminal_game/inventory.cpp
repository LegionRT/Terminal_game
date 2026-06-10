#include "inventory.h"
#include "weapon.h"
#include "potion.h"
#include <iostream>
#include <algorithm>

Inventory::~Inventory() {
	for (Item* item : items) delete item;
}

void Inventory::add_item(Item* item) {
	if (item != nullptr) {
		items.push_back(item);
		std::cout << "Item added to inventory: " << item->get_name() << std::endl;
	}
}

void Inventory::add_item_silent(Item* item) {
	if (item != nullptr) items.push_back(item);
}

void Inventory::transfer_all_to(Inventory& dest) {
	for (Item* item : items) dest.add_item(item);
	items.clear();
}

void Inventory::clear() {
	for (Item* item : items) {
		delete item;
	}
	items.clear();
}

bool Inventory::remove_item(int id) {
	auto it = std::find_if(items.begin(), items.end(), [id](const Item* i) { return i->get_id() == id; });
	if (it != items.end()) {
		delete* it;
		items.erase(it);
		return true;
	}
	return false;
}

Item* Inventory::find_item(int id) {
	for (Item* item : items) {
		if (item->get_id() == id) return item;
	}
	return nullptr;
}

void Inventory::show_items() const {
	if (items.empty()) {
		std::cout << "Inventory is empty." << std::endl;
		return;
	}
	std::cout << "--- Inventory ---" << std::endl;
	int index = 1;
	for (const Item* item : items) {
		std::cout << index++ << ". " << item->get_name() << std::endl;
	}
}

std::vector<Weapon*> Inventory::get_weapons() const {
	std::vector<Weapon*> weapons;
	for (Item* item : items) {
		if (Weapon* weapon = dynamic_cast<Weapon*>(item)) weapons.push_back(weapon);
	}
	return weapons;
}

std::vector<Potion*> Inventory::get_potions() const {
	std::vector<Potion*> potions;
	for (Item* item : items) {
		if (Potion* potion = dynamic_cast<Potion*>(item)) potions.push_back(potion);
	}
	return potions;
}