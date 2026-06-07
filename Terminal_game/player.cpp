#include "player.h"
#include <iostream>
#include <limits>
#include "location_factory.h"
#include "logger.h"

Player::Player(std::shared_ptr<Location> startLocation) : currentLocation(std::move(startLocation))
{
}

void Player::play()
{
	bool isRunning = true;

	while (isRunning)
	{
#ifdef _WIN32
		system("cls");
#endif
		currentLocation->init();

		auto actions = currentLocation->getActions();

		std::cout << "\n--- Доступные действия ---\n";
		for (size_t i = 0; i < actions.size(); ++i)
		{
			std::cout << (i + 1) << ". " << actions[i] << "\n";
		}
		std::cout << "Ваш выбор: ";

		int choice;
		if (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ошибка ввода.\n";
#ifdef _WIN32
			system("pause");
#endif
			continue;
		}

     Logger::instance().log(std::string("Player selected action ") + std::to_string(choice) + " in location " + std::to_string(currentLocation->getId()));

		int nextLocationId = currentLocation->handleAction(choice);

       if (nextLocationId == -2)
		{
			std::cout << "Спасибо за игру!\n";
          Logger::instance().log("Player exited game");
			isRunning = false;
			break;
		}
		else if (nextLocationId >= 0)
		{
           std::cout << "\nПереход в локацию " << nextLocationId << "...\n";
			Logger::instance().log(std::string("Transition to location ") + std::to_string(nextLocationId));
#ifdef _WIN32
			system("pause");
#endif
			// Получаем локацию через фабрику — кеширует и возвращает shared_ptr
			currentLocation = LocationFactory::get(nextLocationId);
		}
		else
		{
#ifdef _WIN32
			system("pause");
#endif
		}
	}
}
