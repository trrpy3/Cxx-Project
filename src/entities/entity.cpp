#include "entity.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Entity::Entity(int hp, int damage, int defense, int projectile_defense, int level)
    : hp(hp), damage(damage), defense(defense), projectile_defense(projectile_defense), level(level) {
}

int Entity::getHp() const { return hp; }
void Entity::setHp(int hp) { this->hp = hp; }
bool Entity::isAlive() const { return hp > 0; }

int Entity::getDamage() const { return damage; }
int Entity::getDefense() const { return defense; }
int Entity::getProjectileDefense() const { return projectile_defense; }

void Entity::attack(Entity* target) {
    if (!target || !isAlive()) return;
    target->takeDamage(getDamage(), damage_Type::melee);
}

void Entity::takeDamage(int amount, damage_Type type) {
    int effectiveDefense = (type == damage_Type::melee) ? getDefense() : getProjectileDefense();
    int damageTaken = amount - effectiveDefense;
    if (damageTaken < 0) damageTaken = 0;
    hp -= damageTaken;
    if (hp < 0) hp = 0;
    std::cout << getTypeName() << " took " << damageTaken << " damage, hp now " << hp << std::endl;
}