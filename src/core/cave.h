#pragma once
#include "location.h"
#include "enemy.h"
#include <vector>
class Cave : public Location {
public:
    Cave(const std::string& name);
    void enter(Player& player) override;
private:
    void startEncounter(Player& player);
    std::vector<Enemy> possibleEnemies;
};