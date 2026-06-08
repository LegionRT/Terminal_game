#pragma once
#include "entity.h"
#include "inventory.h"
#include <string>

class Enemy : public Entity {
private:
    std::string description;
    Inventory inventory;
    bool boss = false;

public:
    Enemy(const std::string& n, int hp, int dmg, const std::string& desc = "", bool isBoss = false)
        : Entity(n, hp, dmg), description(desc), boss(isBoss) {}

    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;
    Enemy(Enemy&&) = default;
    Enemy& operator=(Enemy&&) = default;
    bool isBoss() const { return boss; }

    void drop_loot(Inventory& inv);
    const std::string& get_description() const { return description; }
};
