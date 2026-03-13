#pragma once

#include <string>
#include "enums.h"

class Weapon {
public:
    Weapon(int damage, float accuracy, damage_Type type);
    virtual ~Weapon() = default;
    int getDamage() const;
    float getAccuracy() const;
    damage_Type getType() const;
    virtual std::string getTypeName() const = 0;
protected:
    int damage;
    float accuracy;
    damage_Type type;
};