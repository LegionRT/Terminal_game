#include "puzzle.h"

Puzzle::Puzzle(std::string puzzleName)
	: puzzleId(0), name(puzzleName), completed(false)
{
}

std::string Puzzle::getName() const
{
	return name;
}

bool Puzzle::isCompleted() const
{
	return completed;
}

void Puzzle::setCompleted(bool status)
{
	completed = status;
}