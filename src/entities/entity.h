#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <string>
#include "../core/enums.h"
#include "../items/consumables/stuff.h"
#include "../items/armor/armor.h"
#include "../items/weapon/weapon.h"
#include "../items/consumables/effect.h"
#include "dialogue.h"
#include "../core/exceptions.h"

class Entity {
public:
    static constexpr int MAX_HP = 100;
    
    Entity(int hp, int damage, int defense, int projectile_defense, int level);
    virtual ~Entity() = default;

    int getHp() const;
    void setHp(int hp);
    bool isAlive() const;

    virtual int getDamage() const;
    virtual int getDefense() const;
    int getLevel() const { return level; }
    virtual int getProjectileDefense() const;

    virtual int attack(Entity* target);
    int takeDamage(int amount, damage_Type type);

    virtual std::string getTypeName() const = 0; 

    void addEffect(Effect e);
    void heal(int amount) {
        hp += amount;
        if (hp > MAX_HP) hp = MAX_HP;
    }
    void applyEffects();

protected:
    int hp;
    int damage;
    int defense;
    int level;
    int projectile_defense;
    std::vector<Effect> effects;
};