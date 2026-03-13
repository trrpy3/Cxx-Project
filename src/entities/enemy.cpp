// enemy.cpp
#include "enemy.h"
#include <iostream>
Enemy::Enemy(const std::string& name, int hp, int damage, int defense, int projectile_defense, int level,
    int expReward, int moneyReward, damage_Type attackType, const std::string& art)
    : Entity(hp, damage, defense, projectile_defense, level), name(name), expReward(expReward), moneyReward(moneyReward),
    attackType(attackType), art(art) {
}
void Enemy::render() const {
    std::cout << art << std::endl;
}
void Enemy::attack(Entity* target) {
    if (!target || !isAlive()) return;
    int dmg = getDamage();
    int levelDiff = target->getLevel() - getLevel();
    if (levelDiff > 0) {
        dmg = static_cast<int>(dmg * (1.0f + 0.1f * levelDiff));
        std::cout << "Player is higher level! Enemy damage increased by " << (levelDiff * 10) << "%\n";
    }
    target->takeDamage(dmg, attackType);
}