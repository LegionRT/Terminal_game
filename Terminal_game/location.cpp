#include "location.h"
#include "location.h"
#include <iostream>
#include "location_factory.h"
#include "logger.h"

Location::Location(int id)
	: locationId(id),
	locationName(Map::getLocationNameById(id)),
	map(id)
{
}

void Location::addDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum)
{
	map.addOrUpdateDoorAt(x, y, targetId, isLocked, puzzleNum);
}

bool Location::unlockDoorToLocation(int sourceId, int matchX, int matchY)
{
	auto &doors = map.getDoors();

	// Сначала попробуем найти дверь по координатам (если заданы)
	if (matchX >= 0 && matchY >= 0)
	{
		for (auto &d : doors)
		{
			if (d.getX() == matchX && d.getY() == matchY && d.getTargetLocationId() == sourceId)
			{
				if (d.isLocked())
				{
					d.unlock();
					map.setTile(d.getX(), d.getY(), TileType::Door);
				}
				return true;
			}
		}
	}

	// Иначе — найдём любую дверь, ведущую в sourceId
	for (auto &d : doors)
	{
		if (d.getTargetLocationId() == sourceId)
		{
			if (d.isLocked())
			{
				d.unlock();
				map.setTile(d.getX(), d.getY(), TileType::Door);
			}
			return true;
		}
	}

	return false;
}

void Location::init()
{
	std::cout << "Вы вошли в " << locationName << "!" << std::endl;
	map.draw();

	Logger::instance().log(std::string("Entered location ") + std::to_string(locationId));
}

int Location::getId() const
{
	return locationId;
}

std::vector<std::string> Location::getActions()
{
	std::vector<std::string> actions;

	auto& doors = map.getDoors();
	for (size_t i = 0; i < doors.size(); ++i)
	{
		const Door& d = doors[i];
		std::string state = d.isLocked() ? "(закрыта)" : "(открыта)";
		actions.emplace_back("Дверь " + std::to_string(i + 1) + " " + state + " -> Ведёт в локацию " + std::to_string(d.getTargetLocationId()) + " (позиция: " + std::to_string(d.getX()) + "," + std::to_string(d.getY()) + ")");
	}

	actions.emplace_back("Выйти из игры");
	return actions;
}

int Location::handleAction(int choice)
{
	auto actions = getActions();
	if (choice < 1 || choice > static_cast<int>(actions.size()))
	{
		std::cout << "Некорректный выбор.\n";
		return -1;
	}

	auto& doors = map.getDoors();
	int exitIndex = static_cast<int>(doors.size()) + 1;
	if (choice == exitIndex)
		return -2;

	int doorIndex = choice - 1;
	if (doorIndex < 0 || doorIndex >= static_cast<int>(doors.size()))
	{
		std::cout << "Некорректный выбор двери.\n";
		return -1;
	}

	Door& d = doors[doorIndex];
	int target = d.getTargetLocationId();
	if (target < 0)
	{
		std::cout << "Эта дверь никуда не ведёт.\n";
		return -1;
	}

	if (!d.isLocked())
	{
		std::cout << "Дверь открыта. Переход в локацию " << target << "...\n";

		// При переходе попробуем сначала разблокировать уже существующую дверь
		// в целевой локации, ведущую к нам. Если такой нет — добавим возвращающую.
		if (target >= 0)
		{
			auto targetLoc = LocationFactory::get(target);
			int oppX = d.getX();
			int oppY = d.getY();
			if (d.getX() == 0) oppX = Map::getWidth() - 1;
			else if (d.getX() == Map::getWidth() - 1) oppX = 0;
			if (d.getY() == 0) oppY = Map::getHeight() - 1;
			else if (d.getY() == Map::getHeight() - 1) oppY = 0;

			if (!targetLoc->unlockDoorToLocation(locationId, oppX, oppY))
			{
				targetLoc->addDoorAt(oppX, oppY, locationId, false, locationId % 3 + 1);
			}
		}

		return target;
	}

    // Делегируем проверку двери самому объекту Door
	bool nowOpen = d.interact();
	if (nowOpen)
	{
		// если разблокирована, обновим тайл и перейдём
		map.setTile(d.getX(), d.getY(), TileType::Door);

		// Убедимся, что в целевой локации есть дверь обратно к нам и разблокируем её.
		if (target >= 0)
		{
			auto targetLoc = LocationFactory::get(target);
			// Сначала попробуем найти уже существующую дверь, ведущую в нашу локацию,
			// и разблокировать её. Это нужно, потому что двери генерируются
			// случайно при создании локации и может уже существовать дверь в другом месте.
			if (!targetLoc->unlockDoorToLocation(locationId))
			{
				// Если такой двери нет, добавим возвращающую на противоположной стороне
				int oppX = d.getX();
				int oppY = d.getY();
				if (d.getX() == 0) oppX = Map::getWidth() - 1;
				else if (d.getX() == Map::getWidth() - 1) oppX = 0;
				if (d.getY() == 0) oppY = Map::getHeight() - 1;
				else if (d.getY() == Map::getHeight() - 1) oppY = 0;

				targetLoc->addDoorAt(oppX, oppY, locationId, false, locationId % 3 + 1);
			}
		}

		return target;
	}

	return -1;
}
