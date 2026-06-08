#pragma once
#include "player.h"
#include "entity.h"

class CombatSystem {
private:
	Player& player;
	Entity& opponent;

	void playerTurn();
	void enemyTurn();

public:
	CombatSystem(Player& p, Entity& opponent) : player(p), opponent(opponent) {}
	bool startBattle();
};
