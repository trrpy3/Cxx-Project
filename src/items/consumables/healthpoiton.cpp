#include "healthpotion.h"
HealthPotion::HealthPotion(const std::string& name, int cost, int heal, int minLevel)
    : Stuff(cost), heal(heal), minLevel(minLevel), name(name) {
}
int HealthPotion::getHeal() const { return heal; }
int HealthPotion::getMinLevel() const { return minLevel; }
std::string HealthPotion::getType() const { return "HealthPotion"; }