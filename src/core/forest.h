#pragma once
#include "location.h"
#include "../entities/player.h"
#include "../entities/enemy.h"
#include <chrono> 
class Forest : public Location {
public:
    Forest(const std::string& name);
    void enter(Player& player) override;
private:
    void startEncounter(Player& player);
    std::vector<Enemy> enemyPool;  
    bool firstVisit = true;         
    std::chrono::steady_clock::time_point lastEncounter;
};