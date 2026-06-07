#include "math_puzzle.h"
#include <iostream>
#include <random>
#include "logger.h"

MathPuzzle::MathPuzzle()
	: Puzzle("Math"),
	  a(0),
	  b(0)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 10);
	a = dist(gen);
	b = dist(gen);
}

void MathPuzzle::start()
{
	std::cout << "Сколько будет " << a << " + " << b << "?\n";
}

bool MathPuzzle::solve()
{
	int x;
	std::cin >> x;
	return x == (a + b);
}

bool MathPuzzle::play()
{
	start();
	bool ok = solve();
	setCompleted(ok);
	return ok;
}