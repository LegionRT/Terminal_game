#include "enemy.h"
#include "item.h" 
#include "weapon.h" 
#include "potion.h" 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> 

Enemy::Enemy(const char* n, int hp, int dng, const char* desc)
    : Entity(std::string(n), hp, dng), description(desc) { // Исправили тип на std::string и опечатку dng/dmg
        std::cout << "Враг создан: " << get_name() << std::endl; // Исправили getName() на get_name()
}

void Enemy::drop_loot(Inventory& player_inventory) {
    std::cout << "\n" << get_name() << " побеждён! Вы получаете лут: " << std::endl; // Исправили getName() на get_name()

    auto& weapons = loot_inventory.get_weapons();
    auto& potions = loot_inventory.get_potions();

    for (auto* weapon : weapons)
    {
        std::cout << "_ " << weapon->get_name() << std::endl;
        player_inventory.add_item(weapon);
    }

    for (auto& potion : potions) {
        std::cout << "_ " << potion->get_name() << std::endl;
        player_inventory.add_item(potion);
    }

    weapons.clear();
    potions.clear();
}