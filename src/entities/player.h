#pragma once

#include "entity.h"
#include "../items/consumables/stuff.h"
#include "../items/consumables/effect.h"
#include "../items/consumables/healthpotion.h"
#include "../items/weapon/weapon.h"
#include "../items/armor/armor.h"
#include <vector>
#include <memory>
#include <optional>

class Player : public Entity {
public:
    static constexpr int MAX_HP = 100;

    Player(int hp, int damage, int defense, int projectile_defense, int level, int luck, int money);
    int getDamage() const override;
    int getDefense() const override;
    int getProjectileDefense() const override;
    int attack(Entity* target) override;
    std::string getTypeName() const override { return "Player"; }
    void addStuff(std::unique_ptr<Stuff> item);
    void addWeapon(std::unique_ptr<Weapon> item);
    void addArmor(std::unique_ptr<Armor> item);
    void setActiveWeapon(Weapon* weapon);
    void setActiveHelmet(Helmet* helmet);
    void setActiveChestplate(Chestplate* chestplate);
    void equipWeapon(int index);
    void equipHelmet(int index);
    void equipChestplate(int index);
    bool useStuff(int index);
    std::optional<Stuff*> findStuff(const std::string& type) const;
    void showInventory() const;
    void showEquipment() const;
    void gainExp(int amount);
    int getExp() const { return exp; }
    int getLevel() const { return level; }
    int getMoney() const { return money; }
    void spendMoney(int amount) { money -= amount; }
    void addMoney(int amount) { money += amount; }
    int getLuck() const { return luck; }
    size_t getWeaponCount() const { return weaponInv.size(); }
    size_t getArmorCount() const { return armourInv.size(); }
private:
    int luck;
    int level;
    int money;
    int exp;
    int expToNextLevel;
    std::vector<std::unique_ptr<Stuff>> stuffInv;
    std::vector<std::unique_ptr<Weapon>> weaponInv;
    std::vector<std::unique_ptr<Armor>> armourInv;
    Weapon* activeWeapon;
    Helmet* activeHelmet;
    Chestplate* activeChestplate;
};
