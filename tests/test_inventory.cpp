#include <gtest/gtest.h>
#include "player.h"
#include "healthpotion.h"
#include "armor.h"

class InventoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_unique<Player>(100, 10, 5, 3, 1, 5, 100);
    }
    
    std::unique_ptr<Player> player;
};

TEST_F(InventoryTest, AddStuff) {
    auto potion = std::make_unique<HealthPotion>("Health Potion", 50, 1, 30);
    player->addStuff(std::move(potion));

    auto found = player->findStuff("Health Potion");
    EXPECT_TRUE(found.has_value());
}

TEST_F(InventoryTest, UseInvalidIndexReturnsFalse) {
    EXPECT_FALSE(player->useStuff(0));
    EXPECT_FALSE(player->useStuff(-1));
}

TEST_F(InventoryTest, EquipInvalidIndexDoesNothing) {
    EXPECT_NO_THROW(player->equipWeapon(0));
    EXPECT_NO_THROW(player->equipHelmet(0));
    EXPECT_NO_THROW(player->equipChestplate(0));
}

TEST_F(InventoryTest, AddArmor) {
    auto helmet = std::make_unique<Helmet>("Iron Helmet", 5, 3);
    player->addArmor(std::move(helmet));

    player->equipHelmet(0);

}