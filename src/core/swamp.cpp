#include "swamp.h"
#include "battle.h"
#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

Swamp::Swamp(const std::string& name) : Location(name) {}

void Swamp::startEncounter(Player& player) {
    Enemy kikimora("Kikimora", 50, 10, 3, 2, 3, 20, 20, damage_Type::range,
        "      (o_o)      \n      /| |\\      \n       | |       \n      /   \\      \n     /     \\     \n    /       \\    \n   /         \\   \n");
    bool escaped = false;
    bool defeated = false;
    battle(player, kikimora, escaped, defeated);
    if (!player.isAlive()) return;
    if (defeated) {
        player.gainExp(kikimora.getExpReward());
        player.addMoney(kikimora.getMoneyReward());
        std::cout << "You gained " << kikimora.getExpReward() << " exp and " << kikimora.getMoneyReward() << " money.\n";
    }
    lastEncounter = std::chrono::steady_clock::now();
}

void Swamp::enter(Player& player) {
    clearScreen();
    std::cout << "You enter the murky swamp...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (firstVisit) {
        firstVisit = false;
        startEncounter(player);
        if (!player.isAlive()) return;
    }
    else {
        int waitTime = 8 + rand() % 13;
        auto waitUntil = std::chrono::steady_clock::now() + std::chrono::seconds(waitTime);
        std::cout << "You wade through the swamp.\n";
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

    std::cout << "You can go back to forest or forward to mountain.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}