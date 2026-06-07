#pragma once
#include "location.h"
#include <memory>

class Player
{
private:
	std::shared_ptr<Location> currentLocation;

public:
	Player(std::shared_ptr<Location> startLocation);
	~Player() = default;

	// Основной игровой цикл
	void play();
};
