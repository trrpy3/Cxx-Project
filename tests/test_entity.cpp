#include <gtest/gtest.h>
#include "entity.h"
#include "enums.h"

class TestEntity : public Entity {
public:

    TestEntity(int hp, int damage, int defense, int projectile_defense, int level = 1)
        : Entity(hp, damage, defense, projectile_defense, level) {}  
    
    std::string getTypeName() const override { return "TestEntity"; }
};

TEST(EntityTest, ConstructorWorks) {
    TestEntity entity(100, 20, 10, 5, 1);
    EXPECT_EQ(entity.getHp(), 100);
    EXPECT_TRUE(entity.isAlive());
}

TEST(EntityTest, TakeDamage) {
    TestEntity entity(100, 20, 10, 5, 3);
    entity.takeDamage(30, damage_Type::melee);
    EXPECT_EQ(entity.getHp(), 80);
}