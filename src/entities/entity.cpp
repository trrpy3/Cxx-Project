#include "entity.h"
#include "../items/consumables/effect.h"
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

int Entity::attack(Entity* target) {
    if (!target || !isAlive()) return 0;
    int dmg = target->takeDamage(getDamage(), damage_Type::melee);
    return dmg;
}

int Entity::takeDamage(int amount, damage_Type type) {

    int effectiveDefense = (type == damage_Type::melee) ? getDefense() : getProjectileDefense();
    
    int damageTaken;
    if (effectiveDefense > amount) {
        damageTaken = 0;
    } else {
        damageTaken = amount - effectiveDefense;
    }
    
    if (damageTaken < 0) damageTaken = 0;
    
    hp -= damageTaken;
    if (hp < 0) hp = 0;
    return damageTaken;
}

void Entity::addEffect(Effect e) {
    effects.push_back(e);
}


void Entity::applyEffects() {
    auto it = effects.begin();
    while (it != effects.end()) {
        std::visit([this](auto& effect) {
            effect.apply(*this);
        }, *it);
        
        it = effects.erase(it);
    }
}

// void Entity::applyEffects() {
//     auto it = effects.begin();
//     while (it != effects.end()) {
//         std::visit([this](auto& effect) {
//             effect.apply(*this);
//         }, *it);
        
//         if (std::visit([](auto& effect) { return effect.duration; }, *it) > 0) {
//             std::visit([](auto& effect) { effect.duration--; }, *it);
//         }
        
//         if (std::visit([](auto& effect) { return effect.duration; }, *it) <= 0) {
//             it = effects.erase(it);
//         } else {
//             ++it;
//         }
//     }
// }