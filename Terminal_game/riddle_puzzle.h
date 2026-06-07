#pragma once
#include "puzzle.h"
#include <string>

class RiddlePuzzle : public Puzzle
{
private:
	std::string question;
	std::string answer;

public:
	RiddlePuzzle();

	void start() override;
	bool solve() override;
	bool play() override;
};