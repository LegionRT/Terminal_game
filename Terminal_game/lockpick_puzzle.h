#pragma once
#include "puzzle.h"
#include <vector>

class LockpickPuzzle : public Puzzle
{
private:
	std::vector<int> pins;     // правильные штифты
	std::vector<bool> state;    // поднятые или нет

public:
	LockpickPuzzle();

	void start() override;
	bool solve() override;
	bool play() override;

private:
	void render();
	void reset();
};