#pragma once
#include <memory>

class Location;

class LocationFactory
{
public:
    // Возвращает shared_ptr к локации; кеширует ранее созданные локации.
    static std::shared_ptr<Location> get(int id);
};
