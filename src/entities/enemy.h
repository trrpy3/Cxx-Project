#pragma once
#include "entity.h"
#include "../items/consumables/effect.h"
#include <string>
class Enemy : public Entity {
public:
    Enemy(const std::string& name, int hp, int damage, int defense, int projectile_defense, int level,
        int expReward, int moneyReward, damage_Type attackType, const std::string& art);
    std::string getTypeName() const override { return "Enemy"; }
    int getExpReward() const { return expReward; }
    int getMoneyReward() const { return moneyReward; }
    damage_Type getAttackType() const { return attackType; }
    int getLevel() const { return level; }
    void render() const;
    int attack(Entity* target) override;
    //int takeDamage(int amount, damage_Type type) override;
private:
    std::string name;
    int level;
    int expReward;
    int moneyReward;
    damage_Type attackType;
    std::string art;
};
