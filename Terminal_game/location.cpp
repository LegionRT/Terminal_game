#include "location.h"
#include <iostream>
#include "map.h"
	Location::Location(int id)
		: locationId(id),
		locationName(Map::getLocationNameById(id)),
		map(id)
	{}

	void Location::init()
	{
		std::cout << "Вы вошли в " << locationName << "!" << std::endl;
		map.draw();
	}