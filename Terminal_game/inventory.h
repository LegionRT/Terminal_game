#pragma once
#include "item.h"
#include "weapon.h" 
#include "potion.h"
#include <vector>
#include <string>

class Inventory {
    private:
    std::vector<Item*> items;

    public:
    Inventory() = default;
    ~Inventory();
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory(Inventory&& other) noexcept : items(std::move(other.items)) {}
    Inventory& operator=(Inventory&& other) noexcept {
        if (this != &other) {
            for (Item* item : items) delete item;
            items = std::move(other.items);
        }
        return *this;
    }

    void add_item(Item* item);
    void add_item_silent(Item* item);

    bool remove_item(int id);
    Item* find_item(int id);
    bool is_empty() const { return items.empty(); }

    void transfer_all_to(Inventory& dest);

    void show_items() const;

    std::vector<Weapon*>& get_weapons();
    std::vector<Potion*>& get_potions();
};