#include <gtest/gtest.h>
#include "healthpotion.h"
#include "armor.h"

TEST(ItemsTest, HealthPotionCreation) {
    HealthPotion potion("Healing Potion", 50, 1, 30);
    
    EXPECT_EQ(potion.getType(), "Health Potion");
}

TEST(ItemsTest, HelmetCreation) {

    Helmet helmet("Dragon Helm", 20, 15);
    

}

TEST(ItemsTest, ChestplateCreation) {
    Chestplate chest("Steel Chestplate", 30, 50);
    

}

