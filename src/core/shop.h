#pragma once
#include "location.h"
#include <vector>
#include <memory>
#include "weapon.h"
#include "player.h"
#include "../items/armor/armor.h"
#include "healthpotion.h"
class Shop : public Location {
public:
    Shop(const std::string& name);
    void addWeapon(std::unique_ptr<Weapon> item);
    void addArmor(std::unique_ptr<Armor> item);
    void addPotion(std::unique_ptr<HealthPotion> item);
    void enter(Player& player);
private:
    std::vector<std::unique_ptr<Weapon>> allWeapons;
    std::vector<std::unique_ptr<Armor>> allArmors;
    std::vector<std::unique_ptr<HealthPotion>> allPotions;
};