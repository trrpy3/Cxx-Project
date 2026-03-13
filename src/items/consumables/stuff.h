#pragma once

#include <string>

class Stuff {
public:
    Stuff(int cost);
    virtual ~Stuff() = default;
    int getCost() const;
    virtual std::string getType() const = 0;
protected:
    int cost;
};