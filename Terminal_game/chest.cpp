#include "chest.h"
#include "potion.h"
#include "weapon.h"
#include <iostream>

void Chest::generate_loot(int mapId) {
    contents.add_item_silent(new Potion("Healing Potion", 8 + mapId * 2));
    contents.add_item_silent(new Potion("Minor Healing Potion", 5 + mapId));
    if (mapId % 2 == 0) {
        contents.add_item_silent(new Weapon("Rusty Dagger", 2 + mapId));
    } else {
        contents.add_item_silent(new Weapon("Iron Sword", 3 + mapId));
    }
}

bool Chest::is_empty() const {
    return contents.is_empty();
}

void Chest::interact(Inventory& playerInv) {
    if (is_empty()) {
        std::cout << "The chest is empty.\n";
        return;
    }

    if (!opened) {
        std::cout << "You opened the chest!\n";
        opened = true;
    }

    std::cout << "Chest contents:\n";
    contents.show_items();
    contents.transfer_all_to(playerInv);
    std::cout << "You took all items from the chest.\n";
}
