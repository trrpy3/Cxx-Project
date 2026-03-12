#pragma once
#include "weapon.h"
#include <string>
#include "enums.h"
class Sword : public Weapon {
public:
    Sword(const std::string& name, int damage, float accuracy, int price = 0, int minLevel = 1);
    std::string getTypeName() const override;
};
