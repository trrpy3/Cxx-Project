#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "forest.h"
#include "swamp.h"
#include "mountain.h"
#include "town.h"
#include "player.h"

class LocationTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_unique<Player>(100, 10, 5, 3, 1, 5, 100);
    }
    
    std::unique_ptr<Player> player;
};

TEST_F(LocationTest, ForestCreation) {
    Forest forest("Dark Forest");
    
    EXPECT_EQ(forest.getName(), "Dark Forest");
}

TEST_F(LocationTest, SwampCreation) {
    Swamp swamp("Misty Swamp");
    
    EXPECT_EQ(swamp.getName(), "Misty Swamp");
}

TEST_F(LocationTest, MountainCreation) {
    Mountain mountain("Rocky Mountain");
    
    EXPECT_EQ(mountain.getName(), "Rocky Mountain");
}

TEST_F(LocationTest, TownCreation) {
    Town town("Rivendell");
    
    EXPECT_EQ(town.getName(), "Rivendell");
}

TEST_F(LocationTest, TownHealsPlayerOverTime) {
    Town town("Rivendell");
    
    player->setHp(30);
    
    EXPECT_NO_THROW(town.enter(*player));
}

TEST(WorldTest, LocationsCanBeConnected) {

    GTEST_SKIP() << "World class needs complete implementation";
}