#include <iostream>
#include "location_factory.h"
#include "player.h"
#include "save_manager.h"
#include <windows.h>

int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	std::cout << "1. New game\n";
	std::cout << "2. Load game\n";
	std::cout << "Choice: ";

	int choice;
	std::cin >> choice;

	std::shared_ptr<Location> startLoc;
	Player* player = nullptr;

	if (choice == 2) {
		auto tempLoc = LocationFactory::get(1);
		Player tempPlayer(tempLoc);
		if (SaveManager::load_game(tempPlayer)) {
			std::cout << "Game loaded successfully!\n";
			player = new Player(std::move(tempLoc)); 						SaveManager::load_game(*player);
		}
		else {
			std::cout << "Save file not found. Starting new game.\n";
			startLoc = LocationFactory::get(1);
			player = new Player(startLoc);
		}
	}
	else {
		startLoc = LocationFactory::get(1);
		player = new Player(startLoc);
	}

	player->play();

	delete player;
	return 0;
}
