#pragma once

#include <string>
#include "../../core/enums.h"

class Weapon {
public:
    Weapon(const std::string& name, int damage, float accuracy, damage_Type type, int price = 0, int minLevel = 1);
    virtual ~Weapon() = default;
    int getDamage() const;
    float getAccuracy() const;
    damage_Type getType() const;
    std::string getName() const;
    int getPrice() const;
    int getMinLevel() const;
    virtual std::string getTypeName() const = 0;
protected:
    std::string name;
    int damage;
    float accuracy;
    damage_Type type;
    int price;
    int minLevel;
};
class Sword : public Weapon {
public:
    Sword(const std::string& name, int damage, float accuracy, int price = 0, int minLevel = 1);
    std::string getTypeName() const override;
};
class Bow : public Weapon {
public:
    Bow(const std::string& name, int damage, float accuracy, int price = 0, int minLevel = 1);
    std::string getTypeName() const override;
};
class Morgenstern : public Weapon {
public:
    Morgenstern(const std::string& name, int damage, float accuracy, int bleeding, int price = 0, int minLevel = 1);
    int getBleeding() const;
    std::string getTypeName() const override;
private:
    int bleeding;
};