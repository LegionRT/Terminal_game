#include "door.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <memory>
#include "puzzle.h"
#include "math_puzzle.h"
#include "riddle_puzzle.h"
#include "lockpick_puzzle.h"
#include "logger.h"

Door::Door(int xPos, int yPos, int targetId, bool isLocked, int puzzleNum)
	: x(xPos),
	y(yPos),
	locked(isLocked),
	puzzleNumber(puzzleNum),
	targetLocationId(targetId)
{
}

int Door::getX() const
{
	return x;
}

int Door::getY() const
{
	return y;
}

bool Door::isLocked() const
{
	return locked;
}

void Door::unlock()
{
	locked = false;
}

int Door::getTargetLocationId() const
{
	return targetLocationId;
}

int Door::getPuzzleNumber() const
{
	return puzzleNumber;
}

void Door::setPuzzleNumber(int num)
{
	puzzleNumber = num;
}

bool Door::interact()
{
	if (!locked)
		return true;

	// Создаём нужный пазл на основе номера пазла и делегируем логику
	std::unique_ptr<Puzzle> puzzle;
	switch (puzzleNumber)
	{
	case 1:
		puzzle = std::make_unique<MathPuzzle>();
		break;
	case 2:
		puzzle = std::make_unique<RiddlePuzzle>();
		break;
	case 3:
		puzzle = std::make_unique<LockpickPuzzle>();
		break;
	default:
		// Нет пазла — нельзя открыть
		std::cout << "Эта дверь заблокирована и не имеет пазла.\n";
		return false;
	}

	if (puzzle->play())
	{
       Logger::instance().log(std::string("Door unlocked via puzzle at (") + std::to_string(x) + "," + std::to_string(y) + ") -> target " + std::to_string(targetLocationId));
		unlock();
		std::cout << "Дверь открыта!\n";
		return true;
	}

	Logger::instance().log(std::string("Failed to open door at (") + std::to_string(x) + "," + std::to_string(y) + ") -> target " + std::to_string(targetLocationId));
	std::cout << "Неправильный ответ. Дверь остаётся закрытой.\n";
	return false;
}
