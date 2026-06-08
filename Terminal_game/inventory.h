#pragma once
#include "item.h"
#include "weapon.h" 
#include "potion.h"
#include <vector>
#include <string>

class Inventory {
    private:
    std::vector<Item*> items;

    public:
    ~Inventory();

    void add_item(Item* item);

    bool remove_item(int id);
    Item* find_item(int id);

    void show_items() const;

    std::vector<Weapon*>& get_weapons();
    std::vector<Potion*>& get_potions();
};