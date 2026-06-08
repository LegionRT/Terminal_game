#pragma once
#include "item.h"

class Potion : public Item {
    private:
    int heal_amout;

    public:
    Potion(const std::string& potion_name, int amout_to_heal)
        : Item(1, potion_name), heal_amout(amout_to_heal) {}

    void use() override {
        printf("Вы выпили %s. Восстановлено %d HP.\n", name.c_str(), heal_amout);
    }

    int get_heal_amout() const { return heal_amout; }
};