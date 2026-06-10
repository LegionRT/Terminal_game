#include "enemy.h"
#include <iostream>

void Enemy::drop_loot(Inventory& inv) {
    if (!inventory.is_empty()) {
        std::cout << "The enemy dropped loot:\n";
        inventory.transfer_all_to(inv);
    }
}
