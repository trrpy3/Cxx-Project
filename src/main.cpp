#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include "player.h"
#include "world.h"
#include "user_interface.h"
#include "town.h"
#include "forest.h"
#include "swamp.h"
#include "mountain.h"
#include "cave.h"
#include "shop.h"
#include "weapon.h"
#include "sword.h"
#include "bow.h"
#include "./items/weapon/morgenstern.h"
#include "../items/armor/armor.h"
#include "healthpotion.h"
#include "exceptions.h"

int main() {

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    try {
        Player player(100, 5, 5, 3, 1, 5, 50);

        for (int i = 0; i < 3; ++i) {
            player.addStuff(std::make_unique<HealthPotion>("Small Health Potion", 15, 10));
        }

        auto stick = std::make_unique<Sword>("Stick", 5, 1.0f);
        player.addWeapon(std::move(stick));

        auto woodenChest = std::make_unique<Chestplate>("Wooden Chestplate", 6);
        player.addArmor(std::move(woodenChest));

        player.equipWeapon(0);
        player.equipChestplate(0);

        World world(&player);

        Town* town = world.addLocation<Town>("Town");
        Forest* forest = world.addLocation<Forest>("Forest");
        Swamp* swamp = world.addLocation<Swamp>("Swamp");
        Mountain* mountain = world.addLocation<Mountain>("Mountain");
        Cave* cave = world.addLocation<Cave>("Cave");
        Shop* shop = world.addLocation<Shop>("Shop");

        world.connect("Town", "Forest");
        world.connect("Town", "Swamp");
        world.connect("Town", "Mountain");
        world.connect("Town", "Cave");
        world.connect("Town", "Shop");

        world.connect("Forest", "Swamp");
        world.connect("Swamp", "Mountain");
        world.connect("Mountain", "Cave");

        shop->addWeapon(std::make_unique<Sword>("Wooden Sword", 10, 1.0f, 30, 1));
        shop->addWeapon(std::make_unique<Bow>("Wooden Bow", 10, 0.9f, 30, 1));
        shop->addWeapon(std::make_unique<Sword>("Stone Sword", 25, 1.0f, 75, 4));
        shop->addWeapon(std::make_unique<Bow>("Stone Bow", 25, 0.9f, 75, 4));
        shop->addWeapon(std::make_unique<Sword>("Steel Sword", 50, 1.0f, 120, 8));
        shop->addWeapon(std::make_unique<Bow>("Steel Bow", 50, 0.9f, 120, 8));
        shop->addWeapon(std::make_unique<Morgenstern>("Morgenstern", 75, 0.7f, 10, 200, 10));

        shop->addArmor(std::make_unique<Helmet>("Wooden Helmet", 4, 5, 30, 1));
        shop->addArmor(std::make_unique<Chestplate>("Wooden Chestplate", 6, 30, 1));
        shop->addArmor(std::make_unique<Helmet>("Stone Helmet", 8, 10, 75, 4));
        shop->addArmor(std::make_unique<Chestplate>("Stone Chestplate", 12, 75, 4));
        shop->addArmor(std::make_unique<Helmet>("Steel Helmet", 16, 15, 120, 8));
        shop->addArmor(std::make_unique<Chestplate>("Steel Chestplate", 24, 120, 8));

        shop->addPotion(std::make_unique<HealthPotion>("Health Potion", 30, 30, 3));
        shop->addPotion(std::make_unique<HealthPotion>("Greater Health Potion", 50, 75, 5));

        world.setStartLocation("Town");

        UI ui(world, player);
        ui.run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}