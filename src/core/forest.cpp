#include "forest.h"
#include "battle.h"
#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

Forest::Forest(const std::string& name) : Location(name, location_Type::Ugly, 1) {
    enemyPool = {
        Enemy("Spider", 40, 5, 2, 1, 1, 10, 10, damage_Type::melee,
            "      /\\      \n     /  \\     \n     |  |     \n     |  |     \n     \\__/     \n    /    \\    \n   /      \\   \n  /        \\  \n /          \\ \n"),
        Enemy("Wolf", 60, 8, 3, 2, 2, 20, 15, damage_Type::melee,
            "      /\\_/\\     \n     ( o o )    \n      > ^ <     \n"),
        Enemy("Goblin", 45, 6, 2, 1, 1, 15, 12, damage_Type::melee,
            "      ,     ,    \n     (\\____/)   \n      (_oo_)     \n        (O)      \n       __||__    \n")
    };
}

void Forest::startEncounter(Player& player) {
    if (enemyPool.empty()) return;

    int idx = rand() % enemyPool.size();
    Enemy enemy = enemyPool[idx];
    bool escaped = false;
    bool defeated = false;

    battle(player, enemy, escaped, defeated);

    if (!player.isAlive()) return;

    if (defeated) {
        player.gainExp(enemy.getExpReward());
        player.addMoney(enemy.getMoneyReward());
        std::cout << "You gained " << enemy.getExpReward() << " exp and "
                  << enemy.getMoneyReward() << " money.\n";
    }

    lastEncounter = std::chrono::steady_clock::now();
}

void Forest::enter(Player& player) {
    clearScreen();
    std::cout << "You enter the dark forest...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (firstVisit) {
        firstVisit = false;
        startEncounter(player);
        if (!player.isAlive()) return;
    }
    else {
        int waitTime = 8 + rand() % 13;
        auto waitUntil = std::chrono::steady_clock::now() + std::chrono::seconds(waitTime);

        std::cout << "You wander through the forest.\n";
        std::cout << "Your HP: " << player.getHp() << "/" << Player::MAX_HP << "\n";
        std::cout << "Press '1' to quickly return to previous location.\n";

        while (std::chrono::steady_clock::now() < waitUntil) {
            if (keyPressed()) {
                char cmd = getChar();
                if (cmd == '1') {
                    std::cout << "Returning quickly...\n";
                    return;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        startEncounter(player);
        if (!player.isAlive()) return;
    }
}