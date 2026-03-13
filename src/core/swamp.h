#pragma once
#include "location.h"
#include "enemy.h"
class Swamp : public Location {
public:
    Swamp(const std::string& name);
    void enter(Player& player) override;
private:
    void startEncounter(Player& player);
};