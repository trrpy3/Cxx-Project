#pragma once
#include "location.h"
#include "../entities/player.h"
#include "../entities/enemy.h"
#include <chrono>
class Swamp : public Location {
public:
    Swamp(const std::string& name);
    void enter(Player& player) override;
private:
    void startEncounter(Player& player);
    bool firstVisit = true;  
    std::chrono::steady_clock::time_point lastEncounter;
};