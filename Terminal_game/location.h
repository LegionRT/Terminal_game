#pragma once
#include "map.h"
#include <string>
class Location
{
private:
	int locationId;
	std::string locationName;
	Map map;
public:
	Location(int id);
	void init();
};