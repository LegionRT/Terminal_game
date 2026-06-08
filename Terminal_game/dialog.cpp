#include "dialog.h"
#include <iostream>
#include <limits>

const DialogNode* DialogTree::findNode(int id) const {
	for (const auto& node : nodes) {
		if (node.id == id) return &node;
	}
	return nullptr;
}

void DialogTree::addNode(const DialogNode& node) {
	nodes.push_back(node);
}

bool DialogTree::run(const std::function<void(const DialogOutcome&)>& applyOutcome) {
	int currentId = rootId;
	while (true) {
		const DialogNode* node = findNode(currentId);
		if (!node) {
			std::cout << "Dialog ended.\n";
			return false;
		}

		std::cout << "\n\"" << node->npcLine << "\"\n";

		if (node->choices.empty()) {
			applyOutcome(node->outcome);
			return true;
		}

		for (size_t i = 0; i < node->choices.size(); ++i) {
			std::cout << (i + 1) << ". " << node->choices[i].playerLine << "\n";
		}
		std::cout << "Choice: ";

		int choice = 0;
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.\n";
			continue;
		}

		if (choice < 1 || choice > static_cast<int>(node->choices.size())) {
			std::cout << "Invalid choice.\n";
			continue;
		}

		const DialogChoice& picked = node->choices[static_cast<size_t>(choice - 1)];
		if (picked.nextNodeId < 0) {
			applyOutcome(node->outcome);
			return true;
		}
		currentId = picked.nextNodeId;
	}
}

DialogTree DialogTree::createHermitDialog() {
	DialogTree tree;

	DialogNode root;
	root.id = 0;
	root.npcLine = "Greetings, traveler. I am the Hermit. What do you want?";
	root.choices = {
		{"Who are you?", 1},
		{"I need help.", 2},
		{"Get out of my way!", 3},
		{"I want to fight you!", 4} 	};
	tree.addNode(root);

	DialogNode who;
	who.id = 1;
	who.npcLine = "I have lived in this maze for years. Take care on the deeper floors.";
	who.choices = { {"Thank you.", -1} };
	who.outcome.endDialog = true;
	tree.addNode(who);

	DialogNode help;
	help.id = 2;
	help.npcLine = "You look wounded. Take this greater healing potion.";
	help.choices = { {"Thanks!", -1} };
	help.outcome.endDialog = true;
	help.outcome.givePotion = true;
	help.outcome.potionName = "Greater Healing Potion";
	help.outcome.potionHeal = 20;
	tree.addNode(help);

	DialogNode angry;
	angry.id = 3;
	angry.npcLine = "So be it! Defend yourself!";
	angry.choices = {};
	angry.outcome.endDialog = true;
	angry.outcome.turnHostile = true;
	tree.addNode(angry);

		DialogNode fight;
	fight.id = 4;
	fight.npcLine = "You dare challenge an old man? Very well, prepare to die!";
	fight.choices = {};
	fight.outcome.endDialog = true;
	fight.outcome.turnHostile = true;
	tree.addNode(fight);

	tree.setRoot(0);
	return tree;
}

DialogTree DialogTree::createMerchantDialog() {
	DialogTree tree;

	DialogNode root;
	root.id = 0;
	root.npcLine = "Welcome. I am the Merchant. Need supplies or a way forward?";
	root.choices = {
		{"Got anything useful?", 1},
		{"Can you open a door?", 2},
		{"Goodbye.", -1},
		{"I'm robbing you!", 3} 	};
	root.outcome.endDialog = true;
	tree.addNode(root);

	DialogNode trade;
	trade.id = 1;
	trade.npcLine = "Here, a steel blade. Use it well.";
	trade.choices = { {"Deal.", -1} };
	trade.outcome.endDialog = true;
	trade.outcome.giveWeapon = true;
	trade.outcome.weaponName = "Steel Blade";
	trade.outcome.weaponBonus = 5;
	tree.addNode(trade);

	DialogNode door;
	door.id = 2;
	door.npcLine = "I know the mechanism. Watch the lock click open.";
	door.choices = { {"Nice.", -1} };
	door.outcome.endDialog = true;
	door.outcome.unlockDoor = true;
	tree.addNode(door);

		DialogNode rob;
	rob.id = 3;
	rob.npcLine = "Thief! You think you can just take my goods? I'll teach you a lesson!";
	rob.choices = {};
	rob.outcome.endDialog = true;
	rob.outcome.turnHostile = true;
	tree.addNode(rob);

	tree.setRoot(0);
	return tree;
}