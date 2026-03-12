#pragma once

#include <vector>
#include <memory>
#include <optional>
#include "enums.h"
#include "stuff.h"
#include "armour.h"
#include "weapon.h"
#include "effect.h"
#include "dialogue.h"
#include "exceptions.h"

class Entity {
public:
    Entity(int hp, int damage, int defense, int projectile_defense);
    virtual ~Entity() = default;

    int getHp() const;
    void setHp(int hp);
    bool isAlive() const;

    virtual int getDamage() const;
    virtual int getDefense() const;
    virtual int getProjectileDefense() const;

    virtual void attack(Entity* target);
    virtual void takeDamage(int amount, damage_Type type);

    virtual std::string getTypeName() const = 0; 

    void addEffect(Effect e);
    void applyEffects();

protected:
    int hp;
    int damage;
    int defense;
    int projectile_defense;
    std::vector<Effect> effects;
};