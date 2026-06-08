#include "combat_system.h"
#include "player.h"
#include "enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

CombatSystem::CombatSystem(Player& player, Enemy& enemy)
    : player(player), enemy(enemy){}

void CombatSystem::startBattle() {
    std::cout << "A battle has started!" << std::endl;
    std::cout << "Enemy" << enemy.getName() << "appeared!" << std::endl;
}

void CombatSystem::playerTurn() {
    int choice = 0;

    std::cout << "\nWat will you do?" << std::endl;
    std::cout << "1: FIGHT" << std::endl;
    std::cout << "2: ITEM" << std::endl;
    std::cout << "2: MERCY" << std::endl;
    std::cout << "Your choice: " << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        attack(player.getDamage(), enemy.getHealthRef(), "Player", "Enemy");
        isPlayerTurn = false;
    }
    else if (choice == 2)
    {
        if (player.use_potion())
        {
            std::cout << " You used a potion. HP restored." << std::endl;
        }
        else
        {
            std::cout << "You have no potions!" << std::endl;
        }
        isPlayerTurn = false;
    }
    else if (choice == 3)
    {
        srand(time(0));
        int escapeRoll = rand() % 100;
        if (escapeRoll > 50)
        {
            std::cout << "You spared the enemy. The enemy ran away!" << std::endl;
            endBattle();
            return;
        }
        else
        {
            std::cout << "You tried to spare the enemy, but it didn't work!" << std::endl;
            isPlayerTurn = false;
        }
    }  
}

void CombatSystem::enemyTurn() {
    attack(enemy.getDamage(), player.getHealthRef(), "Enemy", "Player");
    isPlayerTurn = true;
} 

void CombatSystem::endBattle() {
    if (!enemy.is_alive())
    {
        std::cout << "Enemy defenger!" << std::endl;
        enemy.drop_loot(player.get_inventory());
    }
}

void CombatSystem::attack(int attackerDamade, int& defenderHealth, const char* attackerName, const char* defenderName) {
    int damade = calculateDamade(attackerDamade, defenderHealth < 0 ? 0 : defenderHealth);
    defenderHealth -= damade;

    std::cout << attackerName << " attacks " << defenderName << "! ";
    std::cout << defenderName << " takes " << damade << " damade." << std::endl;
}

int CombatSystem::calculateDamade(int attack, int defense) {
    double rawDamade = attack - (0.5 * defense);
    int finalDamage = static_cast<int>(ceil(rawDamade));
    return (finalDamage < 1) ? 1 : finalDamage;
}