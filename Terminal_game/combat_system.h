#pragma once
#include "player.h"
#include "entity.h"

enum class BattleResult {
	Victory,
	Defeat,
	Escaped
};

class CombatSystem {
private:
	Player& player;
	Entity& opponent;
	BattleResult playerTurn();
	void enemyTurn();
public:
	CombatSystem(Player& p, Entity& opponent) : player(p), opponent(opponent) {}
	BattleResult startBattle();
};