#pragma once

#include <string>
class Armor {
public:
    Armor(const std::string& name, int defense, int price = 0, int minLevel = 1);
    virtual ~Armor() = default;
    int getDefense() const;
    std::string getName() const;
    int getPrice() const;
    int getMinLevel() const;
    virtual std::string getType() const = 0;
protected:
    std::string name;
    int defense;
    int price;
    int minLevel;
};
class Helmet : public Armor {
public:
    Helmet(const std::string& name, int defense, int projectile_defense, int price = 0, int minLevel = 1);
    int getProjectileDefense() const;
    std::string getType() const override;
private:
    int projectile_defense;
};
class Chestplate : public Armor {
public:
    Chestplate(const std::string& name, int defense, int price = 0, int minLevel = 1);
    std::string getType() const override;
};