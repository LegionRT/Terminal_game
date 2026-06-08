#pragma once
#include <string>

class Entity {
private:
    int health;
    int damage;
    std::string name;

public:
    Entity(const std::string& n, int hp, int dmg) : name(n), health(hp), damage(dmg) {}
    int getHealth() const { return health; }
    int& getHealthRef() { return health; }
    int getDamage() const { return damage; }
    // Backwards-compatible alias
    int detDamage() const { return getDamage(); }
    const std::string& getName() const { return name; }

    void take_damage(int amount) { health -= amount; if (health < 0) health = 0; }
    void heal(int amount) { health += amount; }
    bool is_alive() const { return health > 0; }
};
