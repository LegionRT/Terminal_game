#pragma once

class Entity {
    private:
    int health;
    int damage;
    const char* name;

    public: 
    Entity(const char* n, int hp, int dmg) : name(n), health(hp), damage(dmg){}
    int getHealth() const { return health; }
    int& getHealthRef() { return health; }
    int detDamage() const { return damage; }
    const char* getName() const { return name; }

    void take_damage(int amount) { health -= amount; if (health < 0) health = 0; }
    void heal(int amount) { health += amount; }
    bool is_alive() const { return health > 0;}
};