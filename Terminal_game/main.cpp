#include <iostream>
#include "location_factory.h"
#include "player.h"
#include "save_manager.h"
#include "platform.h"
int main()
{
initConsole();

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
		if (choice == 2) {
			startLoc = LocationFactory::get(1);
			player = new Player(startLoc);
			if (SaveManager::load_game(*player)) {
				std::cout << "Game loaded successfully!\n";
			}
			else {
				std::cout << "Save file not found or corrupted. Starting new game.\n";
			}
		}
		else {
			startLoc = LocationFactory::get(1);
			player = new Player(startLoc);
		}
	}

	player->play();

	delete player;
	return 0;
}
