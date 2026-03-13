#include "player.h"
#include "../items/consumables/effect.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

Player::Player(int hp, int damage, int defense, int projectile_defense, int level, int luck, int money)
    : Entity(hp, damage, defense, projectile_defense, level), luck(luck), money(money),
    exp(0), expToNextLevel(50), activeWeapon(nullptr), activeHelmet(nullptr), activeChestplate(nullptr) {
}
int Player::getDamage() const {
    int base = 5 + level * 2;
    if (activeWeapon) base += activeWeapon->getDamage();
    return base;
}
int Player::getDefense() const {
    int base = Entity::getDefense() + level;
    if (activeHelmet) base += activeHelmet->getDefense();
    if (activeChestplate) base += activeChestplate->getDefense();
    return base;
}
int Player::getProjectileDefense() const {
    int base = Entity::getProjectileDefense() + level;
    if (activeHelmet) base += activeHelmet->getProjectileDefense();
    return base;
}
void Player::attack(Entity* target) {
    if (!target || !isAlive()) return;
    damage_Type type = activeWeapon ? activeWeapon->getType() : damage_Type::melee;
    int dmg = getDamage();
    float acc = activeWeapon ? activeWeapon->getAccuracy() : 1.0f;
    if ((rand() % 100) < (acc * 100)) {
        int levelDiff = target->getLevel() - getLevel();
        if (levelDiff > 0) {
            dmg = static_cast<int>(dmg * (1.0f + 0.1f * levelDiff));
            std::cout << "Enemy is higher level! Damage increased by " << (levelDiff * 10) << "%\n";
        }
        target->takeDamage(dmg, type);
        if (auto* m = dynamic_cast<Morgenstern*>(activeWeapon)) {
            target->addEffect(BleedingEffect{ m->getBleeding(), 3 });
            std::cout << "Bleeding effect applied!\n";
        }
    }
    else {
        std::cout << "Attack missed!" << std::endl;
    }
}
void Player::addStuff(std::unique_ptr<Stuff> item) { stuffInv.push_back(std::move(item)); }
void Player::addWeapon(std::unique_ptr<Weapon> item) { weaponInv.push_back(std::move(item)); }
void Player::addArmor(std::unique_ptr<Armor> item) { armourInv.push_back(std::move(item)); }
void Player::setActiveWeapon(Weapon* weapon) { activeWeapon = weapon; }
void Player::setActiveHelmet(Helmet* helmet) { activeHelmet = helmet; }
void Player::setActiveChestplate(Chestplate* chestplate) { activeChestplate = chestplate; }
void Player::equipWeapon(int index) {
    if (index >= 0 && index < weaponInv.size()) activeWeapon = weaponInv[index].get();
}
void Player::equipHelmet(int index) {
    if (index >= 0 && index < armourInv.size()) {
        if (auto* h = dynamic_cast<Helmet*>(armourInv[index].get())) activeHelmet = h;
    }
}
void Player::equipChestplate(int index) {
    if (index >= 0 && index < armourInv.size()) {
        if (auto* c = dynamic_cast<Chestplate*>(armourInv[index].get())) activeChestplate = c;
    }
}
bool Player::useStuff(int index) {
    if (index < 0 || index >= stuffInv.size()) return false;
    Stuff* item = stuffInv[index].get();
    if (auto* potion = dynamic_cast<HealthPotion*>(item)) {
        hp += potion->getHeal();
        if (hp > 100) hp = 100;
        std::cout << "Used " << potion->getType() << ", healed " << potion->getHeal() << " HP. Now HP: " << hp << std::endl;
        stuffInv.erase(stuffInv.begin() + index);
        return true;
    }
    return false;
}
std::optional<Stuff*> Player::findStuff(const std::string& type) const {
    auto it = std::find_if(stuffInv.begin(), stuffInv.end(), [&](auto& ptr) { return ptr->getType() == type; });
    if (it != stuffInv.end()) return it->get();
    return std::nullopt;
}
void Player::showInventory() const {
    std::cout << "--- Inventory ---\n";
    std::cout << "Money: " << money << "\n";
    std::cout << "Exp: " << exp << "/" << expToNextLevel << "\n";
    std::cout << "Stuff:\n";
    for (size_t i = 0; i < stuffInv.size(); ++i) {
        auto* p = dynamic_cast<HealthPotion*>(stuffInv[i].get());
        if (p) std::cout << i << ": Health Potion (heal " << p->getHeal() << ")\n";
    }
    std::cout << "Weapons:\n";
    for (size_t i = 0; i < weaponInv.size(); ++i)
        std::cout << i << ": " << weaponInv[i]->getName() << " (damage " << weaponInv[i]->getDamage() << ")\n";
    std::cout << "Armor:\n";
    for (size_t i = 0; i < armourInv.size(); ++i)
        std::cout << i << ": " << armourInv[i]->getName() << " (defense " << armourInv[i]->getDefense() << ")\n";
}
void Player::showEquipment() const {
    std::cout << "--- Equipment ---\n";
    std::cout << "Weapon: " << (activeWeapon ? activeWeapon->getName() : "None") << "\n";
    std::cout << "Helmet: " << (activeHelmet ? activeHelmet->getName() : "None") << "\n";
    std::cout << "Chestplate: " << (activeChestplate ? activeChestplate->getName() : "None") << "\n";
}
void Player::gainExp(int amount) {
    exp += amount;
    while (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        level++;
        expToNextLevel *= 2;
        std::cout << "Level up! Now level " << level << "!\n";
    }
}