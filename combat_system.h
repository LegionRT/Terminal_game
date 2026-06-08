#pragma once 

class Player;
class Enemy;

class CombatSystem {
    public:
    CombatSystem(Player& player, Enemy& enemy);

    void startBattle();
    void playerTurn();
    void enemyTurn();
    void endBattle();

    private:
    Player& player;
    Enemy& enemy;
    bool isPlayerTurn = true;

    void attack(int attackerDamage, int& defenderHealth, const char* attackerName, const char* defenderName);
    int calculateDamade(int attack, int defense);
};