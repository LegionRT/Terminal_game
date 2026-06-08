#include "location_factory.h"
#include "location.h"
#include <map>
#include <memory>
#include <mutex>

std::shared_ptr<Location> LocationFactory::get(int id)
{
    static std::map<int, std::shared_ptr<Location>> cache;
    static std::mutex mtx;

    std::lock_guard<std::mutex> lk(mtx);
    auto it = cache.find(id);
    if (it != cache.end())
    {
        return it->second;
    }

    auto loc = std::make_shared<Location>(id);
    cache[id] = loc;
    return loc;
}
