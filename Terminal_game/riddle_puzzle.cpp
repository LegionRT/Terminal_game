#include "riddle_puzzle.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include "logger.h"

RiddlePuzzle::RiddlePuzzle()
	: Puzzle("Riddle")
{
	std::srand((unsigned)time(nullptr));

	std::vector<std::string> questions =
	{
		"What always runs but never arrives?",
		"How many months in a year have 28 days?",
		"What can you catch but not throw?",
		"What belongs to you but others use it more than you?",
		"What grows down instead of up?"
	};

	int index = rand() % static_cast<int>(questions.size());
	question = questions[index];

	std::vector<std::vector<std::string>> poolAnswers =
	{
		{"tomorrow"},
		{"12", "twelve"},
		{"cold"},
		{"name"},
		{"beard"}
	};
	if (index >= 0 && index < static_cast<int>(poolAnswers.size()))
		answer = poolAnswers[index][0];
}

void RiddlePuzzle::start()
{
	std::cout << "RIDDLE\n\n";
	std::cout << question << "\n\n";

	Logger::instance().log(std::string("Riddle presented: ") + question);
}

bool RiddlePuzzle::solve()
{
	std::string input;
	std::cin >> input;

	std::string lower;
	lower.reserve(input.size());
	for (unsigned char c : input)
		lower.push_back(static_cast<char>(std::tolower(c)));

	std::vector<std::vector<std::string>> poolAnswers =
	{
		{"tomorrow"},
		{"12", "twelve"},
		{"cold"},
		{"name"},
		{"beard"}
	};

	std::vector<std::string> questions =
	{
		"What always runs but never arrives?",
		"How many months in a year have 28 days?",
		"What can you catch but not throw?",
		"What belongs to you but others use it more than you?",
		"What grows down instead of up?"
	};

	int qidx = -1;
	for (size_t i = 0; i < questions.size(); ++i)
	{
		if (questions[i] == question)
		{
			qidx = static_cast<int>(i);
			break;
		}
	}

	if (qidx == -1)
	{
		Logger::instance().log(std::string("Riddle question not recognized: ") + question);
		return false;
	}

	for (auto& opt : poolAnswers[qidx])
	{
		std::string ol;
		ol.reserve(opt.size());
		for (unsigned char c : opt)
			ol.push_back(static_cast<char>(std::tolower(c)));
		if (lower == ol)
		{
			Logger::instance().log(std::string("Riddle answered correctly: input=") + input + " question=" + question);
			return true;
		}
	}

	Logger::instance().log(std::string("Riddle answered incorrectly: input=") + input + " question=" + question);
	return false;
}

bool RiddlePuzzle::play()
{
	start();

	bool result = solve();
	setCompleted(result);

	return result;
}
