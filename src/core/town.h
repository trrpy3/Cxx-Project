#pragma once
#include "location.h"
class Town : public Location {
public:
    Town(const std::string& name);
    void enter(Player& player);
};