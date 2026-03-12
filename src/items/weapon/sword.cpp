#include "sword.h"
Sword::Sword(const std::string& name, int damage, float accuracy, int price, int minLevel)
    : Weapon(name, damage, accuracy, damage_Type::melee, price, minLevel) {
}
std::string Sword::getTypeName() const { return "Sword"; }
