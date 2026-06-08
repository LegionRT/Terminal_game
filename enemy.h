#pragma once
#include "inventory.h" 

class Enemy : public Entity {
    private:
    Inventory loot_inventory;
    const char* description;

    public:
    Enemy(const char* n, int hp, int dmg, const char* desc);

    Inventory& get_loot_inventory() { return loot_inventory; }

    bool getDamage();
    void drop_loot(Inventory& player_inventory);
};