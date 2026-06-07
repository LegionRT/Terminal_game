#include "riddle_puzzle.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

RiddlePuzzle::RiddlePuzzle()
	: Puzzle("Riddle")
{
	std::srand((unsigned)time(nullptr));

	int index = rand() % 5;

	switch (index)
	{
	case 0:
		question = "Что всегда впереди, но его нельзя увидеть?";
		answer = "будущее";
		break;

	case 1:
		question = "Чем больше берёшь, тем больше оставляешь позади?";
		answer = "следы";
		break;

	case 2:
		question = "Что принадлежит тебе, но другие используют чаще?";
		answer = "имя";
		break;

	case 3:
		question = "Что можно сломать, даже не трогая?";
		answer = "обещание";
		break;

	case 4:
		question = "Что растёт, но никогда не живёт?";
		answer = "тень";
		break;
	}
}

void RiddlePuzzle::start()
{
	std::cout << "ЗАГАДКА\n\n";
	std::cout << question << "\n\n";
}

bool RiddlePuzzle::solve()
{
	std::string input;
	std::cin >> input;

	return input == answer;
}

bool RiddlePuzzle::play()
{
	start();

	bool result = solve();
	setCompleted(result);

	return result;
}