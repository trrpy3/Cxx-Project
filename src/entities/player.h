#pragma once
#include "entity.h"

class Player : public Entity {
public:
    int level;
    int luck; // affects enemies' rareness
};