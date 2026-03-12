#pragma once
#include "location.h"
#include "enemy.h"
class Forest : public Location {
public:
    Forest(const std::string& name);
    void enter(Player& player) override;
private:
    void startEncounter(Player& player);
};