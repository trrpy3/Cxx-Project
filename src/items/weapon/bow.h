#include "weapon.h"

Weapon::Weapon(int damage, float accuracy, damage_Type type) : damage(damage), accuracy(accuracy), type(type) {}
int Weapon::getDamage() const { return damage; }
float Weapon::getAccuracy() const { return accuracy; }
damage_Type Weapon::getType() const { return type; }
