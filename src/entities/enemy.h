#pragma once
#include "entity.h"

#include <string>

class Enemy : public Entity {
public:
    int level;
    int rare;
};