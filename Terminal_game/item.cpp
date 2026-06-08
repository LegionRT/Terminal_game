#include "item.h"

int Item::next_id = 1;

Item::Item(const std::string& item_name) : id(next_id++), name(item_name) {}
