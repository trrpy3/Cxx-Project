#include "cave.h"
#include "battle.h"
#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>


Cave::Cave(const std::string& name) 
    : Location(name, location_Type::Ugly, 1)  
{
    firstVisit = true;
}

void Cave::startEncounter(Player& player) {
    Enemy bat("Bat", 30, 8, 2, 2, 4, 20, 15, damage_Type::melee, "        )        \n       /|\\       \n       / \\       \n      /   \\      \n     /     \\     \n    /       \\    \n   /         \\   \n  /           \\  \n");
    bool escaped = false;
    bool defeated = false;
    battle(player, bat, escaped, defeated);
    
    if (!player.isAlive()) return;
    if (defeated) {
        player.gainExp(bat.getExpReward());
        player.addMoney(bat.getMoneyReward());
        std::cout << "You gained " << bat.getExpReward() 
                  << " exp and " << bat.getMoneyReward() << " money.\n";
    }
    lastEncounter = std::chrono::steady_clock::now();
    std::cout << "\nPress any key to continue...";
    getChar();
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
        int waitTime = 5 + rand() % 10;
        auto waitUntil = std::chrono::steady_clock::now() + std::chrono::seconds(waitTime);
        
        std::cout << "You explore deeper into the cave.\n";
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
}