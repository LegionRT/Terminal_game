#pragma once
#include "item.h"

class Weapon : public Item {
    private:
    int bonus_damage;

    public:
    Weapon(const std::string& weapon_name, int damage_bonus)
        : Item(0, weapon_name), bonus_damage(damage_bonus) {}
    
    void use() override {
        printf("Вы экипировали %s. Бонус к урону +%d\n", name.c_str(), bonus_damage);    
    }

    int get_damage_bonus() const { return bonus_damage; }
};