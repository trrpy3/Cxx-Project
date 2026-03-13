#include <gtest/gtest.h>
#include "player.h"
#include "armor.h"
#include "healthpotion.h"

class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_unique<Player>(100, 10, 5, 3, 1, 5, 100);
    }
    
    std::unique_ptr<Player> player;
};

TEST_F(PlayerTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(player->getHp(), 100);
    EXPECT_EQ(player->getLevel(), 1);
    EXPECT_EQ(player->getMoney(), 100);
    EXPECT_TRUE(player->isAlive());
}

TEST_F(PlayerTest, GainExpLevelsUp) {
    EXPECT_EQ(player->getLevel(), 1);
    EXPECT_EQ(player->getExp(), 0);
    
    player->gainExp(50);
    
    EXPECT_GE(player->getLevel(), 1);
}

TEST_F(PlayerTest, HealDoesNotExceedMax) {
    player->setHp(50);
    player->heal(60);
    
    EXPECT_EQ(player->getHp(), Player::MAX_HP);
}

TEST_F(PlayerTest, AddAndUseHealthPotion) {
    auto potion = std::make_unique<HealthPotion>("Health Potion", 50, 1, 30);
    player->addStuff(std::move(potion));
    
    player->setHp(30);
    player->useStuff(0);
    
    EXPECT_EQ(player->getHp(), 60);
}

TEST_F(PlayerTest, EquipArmor) {
    auto helmet = std::make_unique<Helmet>("Iron Helmet", 5, 3);
    player->addArmor(std::move(helmet));
    
    int defenseBefore = player->getDefense();
    int projDefBefore = player->getProjectileDefense();
    
    player->equipHelmet(0);
    
    EXPECT_GT(player->getDefense(), defenseBefore);
    EXPECT_GT(player->getProjectileDefense(), projDefBefore);
}