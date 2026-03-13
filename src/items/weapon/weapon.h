#pragma once

#include "enums.h"
#include <string>

class Weapon {
public:
    std::string name;
    int damage;
    float accurancy;
    int kd_ms;
};