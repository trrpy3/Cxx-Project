#pragma once

#include <variant>

struct BleedingEffect {
    int damagePerTurn;
    int duration;
};
struct HealingEffect {
    int healPerTurn;
    int duration;
};
using Effect = std::variant<BleedingEffect, HealingEffect>;