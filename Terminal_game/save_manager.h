#pragma once
#include <string>

class Player;

class SaveManager {
public:
	static bool save_game(const Player& player, const std::string& filename = "savegame.txt");
	static bool load_game(Player& player, const std::string& filename = "savegame.txt");
};