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
#include "player.h"

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

bool Door::interact(Player& player)
{
	if (!locked)
		return true;

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
		std::cout << "This door is locked and has no puzzle.\n";
		return false;
	}

	if (puzzle->play())
	{
		Logger::instance().log(std::string("Door unlocked via puzzle at (") + std::to_string(x) + "," + std::to_string(y) + ") -> target " + std::to_string(targetLocationId));
		unlock();
		std::cout << "Door unlocked!\n";
		return true;
	}

	Logger::instance().log(std::string("Failed to open door at (") + std::to_string(x) + "," + std::to_string(y) + ") -> target " + std::to_string(targetLocationId));
	const int puzzleDamage = 5;
	player.take_damage(puzzleDamage);
	std::cout << "Wrong answer. The door stays locked. You take " << puzzleDamage << " damage.\n";
	return false;
}
