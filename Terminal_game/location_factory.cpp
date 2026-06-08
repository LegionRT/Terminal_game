#include "location_factory.h"
#include "location.h"
#include <map>
#include <memory>

std::shared_ptr<Location> LocationFactory::get(int id)
{
	static std::map<int, std::shared_ptr<Location>> cache;

	auto it = cache.find(id);
	if (it != cache.end())
	{
		return it->second;
	}
	auto loc = std::make_shared<Location>(id);
	cache[id] = loc;
	return loc;
}