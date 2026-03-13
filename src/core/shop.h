#pragma once
#include "location.h"
#include <vector>
#include <memory>
#include "../items/weapon/weapon.h"
#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../items/armor/armor.h"
#include "../items/consumables/healthpotion.h"
class Shop : public Location {
public:
    Shop(const std::string& name);
    void addWeapon(std::unique_ptr<Weapon> item);
    void addArmor(std::unique_ptr<Armor> item);
    void addPotion(std::unique_ptr<HealthPotion> item);
    void enter(Player& player) override;
private:
    std::vector<std::unique_ptr<Weapon>> allWeapons;
    std::vector<std::unique_ptr<Armor>> allArmors;
    std::vector<std::unique_ptr<HealthPotion>> allPotions;
};