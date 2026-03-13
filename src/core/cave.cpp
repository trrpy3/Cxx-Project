#include "cave.h"
#include "battle.h"
#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

Cave::Cave(const std::string& name) : Location(name) {
    possibleEnemies.push_back(Enemy("Skeleton Warrior", 100, 25, 10, 5, 10, 100, 100, damage_Type::melee,
        "        )        \n       /|\\       \n       / \\       \n      /   \\      \n     /     \\     \n    /       \\    \n   /         \\   \n  /           \\  \n"));
    possibleEnemies.push_back(Enemy("Skeleton Archer", 100, 25, 8, 8, 10, 100, 100, damage_Type::range,
        "        )        \n       /|\\       \n       / \\       \n      /   \\      \n     /     \\     \n    /       \\    \n   /   ===   \\   \n  /   ===   \\  \n"));
}

void Cave::startEncounter(Player& player) {
    int idx = rand() % possibleEnemies.size();
    Enemy enemy = possibleEnemies[idx];
    bool escaped = false;
    bool defeated = false;
    battle(player, enemy, escaped, defeated);
    if (!player.isAlive()) return;
    if (defeated) {
        player.gainExp(enemy.getExpReward());
        player.addMoney(enemy.getMoneyReward());
        std::cout << "You gained " << enemy.getExpReward() << " exp and " << enemy.getMoneyReward() << " money.\n";
    }
    lastEncounter = std::chrono::steady_clock::now();
}

void Cave::enter(Player& player) {
    clearScreen();
    std::cout << "You enter the dark cave...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (firstVisit) {
        firstVisit = false;
        startEncounter(player);
        if (!player.isAlive()) return;
    }
    else {
        int waitTime = 8 + rand() % 13;
        auto waitUntil = std::chrono::steady_clock::now() + std::chrono::seconds(waitTime);
        std::cout << "You explore the cave.\n";
        std::cout << "Your HP: " << player.getHp() << "/100\n";
        std::cout << "Press '1' to return to previous location.\n";

        while (std::chrono::steady_clock::now() < waitUntil) {
            if (keyPressed()) {
                char cmd = getChar();
                if (cmd == '1') {
                    std::cout << "Returning...\n";
                    return;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        startEncounter(player);
        if (!player.isAlive()) return;
    }

    std::cout << "You can go back to mountain.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}