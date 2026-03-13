#pragma once
#include "location.h"
#include "enemy.h"
class Mountain : public Location {
public:
    Mountain(const std::string& name);
    void enter(Player& player) override;
private:
    void startEncounter(Player& player);
};