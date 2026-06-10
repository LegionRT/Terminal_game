#pragma once
#include <memory>

class Location;

class LocationFactory
{
public:
    static std::shared_ptr<Location> get(int id);
};
