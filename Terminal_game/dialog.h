#pragma once
#include <string>
#include <vector>
#include <functional>

struct DialogOutcome {
    bool endDialog = false;
    bool turnHostile = false;
    bool givePotion = false;
    bool giveWeapon = false;
    bool unlockDoor = false;
    std::string potionName;
    int potionHeal = 0;
    std::string weaponName;
    int weaponBonus = 0;
	int mutateNodeId = -1;       // ID ноды, которую хотим изменить (например, 2)
	std::string mutateLine = ""; // Новая реплика NPC для этой ноды
	bool removeReward = false;
};
struct DialogChoice {
    std::string playerLine;
    int nextNodeId;
};

struct DialogNode {
    int id = 0;
    std::string npcLine;
    std::vector<DialogChoice> choices;
    DialogOutcome outcome;
};

class DialogTree {
private:
    std::vector<DialogNode> nodes;
    int rootId = 0;

    const DialogNode* findNode(int id) const;

public:
    void addNode(const DialogNode& node);
    void setRoot(int id) { rootId = id; }
    int getRoot() const { return rootId; }

    void mutateNode(int nodeId, const std::string& newLine, bool removeRewards = true);

    bool run(const std::function<void(const DialogOutcome&)>& applyOutcome);

    static DialogTree createHermitDialog();
    static DialogTree createMerchantDialog();
	static DialogTree createHermitAfterRewardDialog();
	static DialogTree createMerchantAfterRewardDialog();
};
