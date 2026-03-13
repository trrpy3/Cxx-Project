#pragma once

#include "stuff.h"
#include <string>
class HealthPotion : public Stuff {
public:
    HealthPotion(const std::string& name, int cost, int heal, int minLevel = 1);
    int getHeal() const;
    int getMinLevel() const;
    std::string getType() const override;
private:
    int heal;
    int minLevel;
    std::string name;
};