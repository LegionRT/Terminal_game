#include <iostream>
#include "location_factory.h"
#include "player.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	// «апускаем игру с игроком, начина€ с локации 1
	auto start = LocationFactory::get(1);
	Player player(start);
	player.play();
	return 0;
}
