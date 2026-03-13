#pragma once
#include "location.h"
#include "enemy.h"
class Swamp : public Location {
public:
    Swamp(const std::string& name);
    void enter(Player& player);
private:
    void startEncounter(Player& player);
    bool firstVisit = true;  
    std::chrono::steady_clock::time_point lastEncounter;
};