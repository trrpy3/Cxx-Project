#include "armor.h"

Armor::Armor(const std::string& name, int defense, int price, int minLevel)
    : name(name), defense(defense), price(price), minLevel(minLevel) {
}
int Armor::getDefense() const { return defense; }
std::string Armor::getName() const { return name; }
int Armor::getPrice() const { return price; }
int Armor::getMinLevel() const { return minLevel; }
Helmet::Helmet(const std::string& name, int defense, int projectile_defense, int price, int minLevel)
    : Armor(name, defense, price, minLevel), projectile_defense(projectile_defense) {
}
int Helmet::getProjectileDefense() const { return projectile_defense; }
std::string Helmet::getType() const { return "Helmet"; }
Chestplate::Chestplate(const std::string& name, int defense, int price, int minLevel)
    : Armor(name, defense, price, minLevel) {
}
std::string Chestplate::getType() const { return "Chestplate"; }ц