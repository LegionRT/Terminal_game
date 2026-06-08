#pragma once
#include "inventory.h"

class Chest {
private:
    Inventory contents;
    bool opened = false;
public:
    Chest() = default;

    void generate_loot(int mapId);
    bool is_opened() const { return opened; }
    bool is_empty() const;
    void interact(Inventory& playerInv);
};
