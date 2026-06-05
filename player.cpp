#include "player.h"
#include "item.h" // предмет 
#include "weapon.h" // оружие 
#include "potion.h" // зелье 
#include <iostream>

Player::Player(const char* loc) : Entity("Игрок", 20, 5), current_location(loc) {
    std::cout << "Player created at location: " << current_location << std::endl;
}

void Player::show_stats() {
    std::cout << "\n--- Статус игрока ---" << std::endl;
    std::cout << "Имя: " << this -> getName() << std::endl;
    std::cout << "HP: " << this -> getHealth() << "/" << 20 << std::endl;
    std::cout << "Урон: " << this -> getDamage() << std::endl;
    inventory.show_items();
}

bool Player::use_potion() {
    auto& potions = inventory.get_potions();

    if (potions.empty())
    {
        return false;
    }
    
    Potion* potions = potions[0];
    this -> heal(potions -> get_heal_amout());
    std::cout << "Вы выпили " << potions -> get_name() << ". Восстановлено " << potions -> get_heal_amout() << " HP." << std::endl;

    potions.erase(potions.begin());
    return true;
}