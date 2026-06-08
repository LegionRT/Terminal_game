#pragma once
#include "item.h"
#include <cstdio>

class Potion : public Item {
    private:
    int heal_amout;

    public:
    Potion(const std::string& potion_name, int amout_to_heal)
        : Item(potion_name), heal_amout(amout_to_heal) {}

    void use() override {
        printf("You drank %s. Restored %d HP.\n", name.c_str(), heal_amout);
    }

    int get_heal_amout() const { return heal_amout; }
};
