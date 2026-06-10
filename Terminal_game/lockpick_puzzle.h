#pragma once
#include "puzzle.h"
#include <vector>

class LockpickPuzzle : public Puzzle
{
private:
	std::vector<int> pins;
	std::vector<bool> state;

public:
	LockpickPuzzle();

	void start() override;
	bool solve() override;
	bool play() override;

private:
	void render();
	void reset();
};
