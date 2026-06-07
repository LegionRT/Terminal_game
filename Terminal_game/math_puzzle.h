#pragma once
#include "puzzle.h"

class MathPuzzle : public Puzzle
{
private:
	int a, b;

public:
	MathPuzzle();

	void start() override;
	bool solve() override;
	bool play() override;
};