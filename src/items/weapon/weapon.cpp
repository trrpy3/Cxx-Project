#include "weapon.h"

Weapon::Weapon(const std::string& name, int damage, float accuracy, damage_Type type, int price, int minLevel)
    : name(name), damage(damage), accuracy(accuracy), type(type), price(price), minLevel(minLevel) {
}
int Weapon::getDamage() const { return damage; }
float Weapon::getAccuracy() const { return accuracy; }
damage_Type Weapon::getType() const { return type; }
std::string Weapon::getName() const { return name; }
int Weapon::getPrice() const { return price; }
int Weapon::getMinLevel() const { return minLevel; }
Sword::Sword(const std::string& name, int damage, float accuracy, int price, int minLevel)
    : Weapon(name, damage, accuracy, damage_Type::melee, price, minLevel) {
}
std::string Sword::getTypeName() const { return "Sword"; }
Bow::Bow(const std::string& name, int damage, float accuracy, int price, int minLevel)
    : Weapon(name, damage, accuracy, damage_Type::range, price, minLevel) {
}
std::string Bow::getTypeName() const { return "Bow"; }
Morgenstern::Morgenstern(const std::string& name, int damage, float accuracy, int bleeding, int price, int minLevel)
    : Weapon(name, damage, accuracy, damage_Type::melee, price, minLevel), bleeding(bleeding) {
}
int Morgenstern::getBleeding() const { return bleeding; }
std::string Morgenstern::getTypeName() const { return "Morgenstern"; }
