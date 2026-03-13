#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "player.h"
#include "enemy.h"
#include "battle.h"


class CombatTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_unique<Player>(100, 10, 5, 3, 1, 5, 100);
        
        enemy = std::make_unique<Enemy>(
            "Test Goblin", 50, 8, 2, 1, 1, 20, 15, 
            damage_Type::melee, "Goblin art"
        );

        auto sword = std::make_unique<Sword>("Test Sword", 5, 1.0f, 10, 1);
        player->addWeapon(std::move(sword));
        player->equipWeapon(0);
    }
    
    std::unique_ptr<Player> player;
    std::unique_ptr<Enemy> enemy;
};

TEST_F(CombatTest, PlayerAttacksEnemy) {
    int enemyHpBefore = enemy->getHp();
    player->attack(enemy.get());
    
    EXPECT_LT(enemy->getHp(), enemyHpBefore);
}

TEST_F(CombatTest, EnemyAttacksPlayer) {
    int playerHpBefore = player->getHp();
    enemy->attack(player.get());
    
    EXPECT_LT(player->getHp(), playerHpBefore);
}

TEST_F(CombatTest, EnemyDealsMoreDamageToHigherLevelPlayer) {
    player->gainExp(100); 
    
    int playerHpBefore = player->getHp();
    enemy->attack(player.get());
    int damageTaken = playerHpBefore - player->getHp();

    EXPECT_GT(damageTaken, enemy->getDamage() - player->getDefense());
}

TEST_F(CombatTest, BattleFunctionRunsWithoutCrashing) {
    bool escaped = false;
    bool defeated = false;

    EXPECT_NO_THROW(battle(*player, *enemy, escaped, defeated));
}

TEST_F(CombatTest, PlayerCanDie) {
    player->takeDamage(200, damage_Type::melee);
    
    EXPECT_FALSE(player->isAlive());
}

TEST_F(CombatTest, EnemyCanDie) {
    enemy->takeDamage(100, damage_Type::melee);
    EXPECT_FALSE(enemy->isAlive());
}