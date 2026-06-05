#pragma once
#include <string>

class Item {
    protected:
    int id;
    std::string name;

    public:
    Item(int item_id, const std::string& item_name) : id(item_id), name(item_name) {}
    virtual ~Item() = default;
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    virtual void use() = 0;
};