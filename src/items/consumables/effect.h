#pragma once
#include <variant>

class Entity;

struct BleedingEffect {
    int damage;
    int duration;
    
    void apply(Entity& entity);
    
};

struct HealingEffect {
    int amount;
    int duration;
    
    void apply(Entity& entity);  
    
};

using Effect = std::variant<BleedingEffect, HealingEffect>;