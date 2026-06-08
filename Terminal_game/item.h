#pragma once
#include <string>

class Item {
    protected:
    int id;
    std::string name;
    static int next_id;

    public:
    explicit Item(const std::string& item_name);
    virtual ~Item() = default;
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    virtual void use() = 0;
};