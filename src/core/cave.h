#pragma once
#include "location.h"
#include "enemy.h"
#include "player.h"
#include <chrono>

class Cave : public Location {
public:
    Cave(const std::string& name);  
    void enter(Player& player);  

private:
    void startEncounter(Player& player);  
    bool firstVisit = true; 
    std::chrono::steady_clock::time_point lastEncounter;  
};