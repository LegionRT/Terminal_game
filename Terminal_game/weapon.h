#pragma once
#include "item.h"
#include <cstdio>

class Weapon : public Item {
    private:
    int bonus_damage;

    public:
    Weapon(const std::string& weapon_name, int damage_bonus)
        : Item(weapon_name), bonus_damage(damage_bonus) {}
    
    void use() override {
        printf("You equipped %s. Damage bonus +%d\n", name.c_str(), bonus_damage);
    }

    int get_damage_bonus() const { return bonus_damage; }
};
