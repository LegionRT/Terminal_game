#pragma once

#include <string>

class Puzzle
{
private:
	int puzzleId;
	std::string name;
	bool completed;

public:
	Puzzle(std::string puzzleName);
	virtual ~Puzzle() = default;

	virtual void start() = 0;		// запуск головоломки
	virtual bool solve() = 0;		// решение
	virtual bool play() = 0;

	std::string getName() const;
	bool isCompleted() const;
	void setCompleted(bool status);
};