#include "effect.h"
#include "../../entities/entity.h"
#include "../../core/enums.h"
#include <iostream>

void BleedingEffect::apply(Entity& entity) {
    entity.takeDamage(damage, damage_Type::melee);
    std::cout << "Bleeding for " << damage << " damage!" << std::endl;
}

void HealingEffect::apply(Entity& entity) {
    std::cout << "Healing effect not implemented yet!" << std::endl;
}