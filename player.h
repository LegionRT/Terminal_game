#pragma once
#include "entity.h"
#include "inventory.h" 

class Player : public Entity {
    private:
    Inventory inventory; 
    const char* current_location; // Это где будет находиться игрок 

    public: 
    Player(const char* loc); 

    Inventory& get_inventory() { return inventory; }
    const char* get_current_location() { return current_location; }

    bool use_potion(); // Использовать зелье из инвенторя
    bool getDamage();
    void show_stats();
};