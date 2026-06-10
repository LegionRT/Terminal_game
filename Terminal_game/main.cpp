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

	auto startLoc = LocationFactory::get(1);
	Player player(startLoc);

	if (choice == 2)
	{
		if (SaveManager::load_game(player))
		{
			std::cout << "Game loaded successfully!\n";
		}
		else
		{
			std::cout << "Save file not found. Starting new game.\n";
		}
	}

	player.play();
	return 0;
}