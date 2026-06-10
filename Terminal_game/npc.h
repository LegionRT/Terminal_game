#pragma once
#include "entity.h"
#include "dialog.h"
#include <string>

class Player;
class Location;

enum class NpcDisposition {
	Friendly,
	Hostile
};

class Npc : public Entity {
private:
	int npcId;
	NpcDisposition disposition;
	DialogTree dialog;

	void applyOutcome(const DialogOutcome& outcome, Player& player, Location& location);

public:
	Npc(int id, const std::string& name, int hp, int dmg,
		NpcDisposition disp, DialogTree tree);

	int getNpcId() const { return npcId; }
	bool is_hostile() const { return disposition == NpcDisposition::Hostile; }
	bool is_friendly() const { return disposition == NpcDisposition::Friendly; }

		bool has_dialog_left() const { return is_friendly(); }

	void turn_hostile();
	void interact(Player& player, Location& location);
};