#include "mountain.h"
#include "battle.h"
#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

Mountain::Mountain(const std::string& name) 
    : Location(name, location_Type::Ugly, 1) {  
    firstVisit = true;
}

void Mountain::startEncounter(Player& player) {
    Enemy troll("Troll", 75, 15, 5, 3, 6, 50, 50, damage_Type::melee,
        "       /\\_/\\       \n      ( o o )      \n       > ^ <       \n      /     \\      \n     /       \\     \n    /         \\    \n   /           \\   \n  /             \\  \n");
    bool escaped = false;
    bool defeated = false;
    battle(player, troll, escaped, defeated);
    if (!player.isAlive()) return;
    if (defeated) {
        player.gainExp(troll.getExpReward());
        player.addMoney(troll.getMoneyReward());
        std::cout << "You gained " << troll.getExpReward() << " exp and " << troll.getMoneyReward() << " money.\n";
        std::cout << "\nPress any key to continue...";
        getChar();
    }
    lastEncounter = std::chrono::steady_clock::now();
}

void Mountain::enter(Player& player) {
    clearScreen();
    std::cout << "You climb the rocky mountain...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (firstVisit) {
        firstVisit = false;
        startEncounter(player);
        if (!player.isAlive()) return;
    }
    else {
        int waitTime = 8 + rand() % 13;
        auto waitUntil = std::chrono::steady_clock::now() + std::chrono::seconds(waitTime);
        std::cout << "You trek through the mountains.\n";
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

    std::cout << "You can go back to swamp or forward to cave.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}