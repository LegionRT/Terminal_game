#include "lockpick_puzzle.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

LockpickPuzzle::LockpickPuzzle()
	: Puzzle("Lockpick")
{
	reset();
}

void LockpickPuzzle::reset()
{
	pins.clear();
	state.clear();

	int count = rand() % 3 + 3; // 3–5 штифтов

	std::vector<int> all = { 1, 2, 3, 4, 5 };
	std::random_shuffle(all.begin(), all.end());

	for (int i = 0; i < count; i++)
	{
		pins.push_back(all[i]);
		state.push_back(false);
	}
}

void LockpickPuzzle::render()
{
#ifdef _WIN32
	system("cls");
#endif

	std::cout << "=== LOCKPICK PUZZLE ===\n\n";
	std::cout << "Штифты (номера 1-5):\n\n";

	for (size_t i = 0; i < pins.size(); i++)
	{
		std::cout << " [" << pins[i] << "] ";

		if (state[i])
			std::cout << "✔";
		else
			std::cout << "✖";

		std::cout << "\n";
	}

	std::cout << "\nВведите номер штифта: ";
}

void LockpickPuzzle::start()
{
	render();
}

bool LockpickPuzzle::solve()
{
	while (true)
	{
		render();

		int input;
		std::cin >> input;

		bool found = false;

		for (size_t i = 0; i < pins.size(); i++)
		{
			if (pins[i] == input && !state[i])
			{
				state[i] = true;
				found = true;
				break;
			}
		}

		if (!found)
		{
			std::cout << "\n✖ Неверно! Замок сброшен...\n";

#ifdef _WIN32
			system("pause");
#endif

			reset();
			continue;
		}

		bool done = true;
		for (bool s : state)
		{
			if (!s)
			{
				done = false;
				break;
			}
		}

		if (done)
			return true;
	}
}

bool LockpickPuzzle::play()
{
	start();
	bool result = solve();
	setCompleted(result);
	return result;
}