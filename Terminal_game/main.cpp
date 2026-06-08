#include <iostream>
#include "location_factory.h"
#include "player.h"
#include <windows.h>

int main()
{

	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	auto start = LocationFactory::get(1);
	Player player(start);
	player.play();
	return 0;
}
