#include "battle.h"
#include "input.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

void battle(Player& player, Enemy& enemy, bool& escaped, bool& defeated) {
    escaped = false;
    defeated = false;
    int dmg;
    
    clearScreen();
    
    while (player.isAlive() && enemy.isAlive()) {
        player.applyEffects();
        enemy.applyEffects();
        std::cout << "=== Fight with " << enemy.getTypeName() << " (level " << enemy.getLevel() << ") ===\n";

        enemy.render();

        std::cout << "Your HP: " << player.getHp() << "/" << Player::MAX_HP 
                  << ", Enemy HP: " << enemy.getHp() << "\n";
        std::cout << "1 - Attack, 2 - Use item, 3 - Run: ";
        
        int choice;
        std::cin >> choice;
        clearScreen();
        
        switch (choice) {
            case 1:
                dmg = enemy.getHp();
                player.attack(&enemy);
                dmg -= enemy.getHp();
                std::cout << "You dealt " << dmg << " damage!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                break;
                
            case 2: {
                player.showInventory();
                std::cout << "Enter item index to use (-1 to cancel): ";
                int idx;
                std::cin >> idx;
                if (idx == -1) {
                    std::cout << "Cancelled.\n";
                } else if (!player.useStuff(idx)) {
                    std::cout << "Invalid item or cannot use.\n";
                }
                std::cout << "Press any key to continue...";
                getChar();
                ::clearScreen();
                break;
            }
            
            case 3: {
                int escapeChance = 70;
                if (std::rand() % 100 < escapeChance) {
                    std::cout << "You fled!\n";
                    escaped = true;
                    std::cout << "\nPress any key to continue...";
                    getChar(); 
                    ::clearScreen();
                    return;
                } else {
                    std::cout << "Failed to flee!\n";
                    std::cout << "\nPress any key to continue...";
                    getChar();
                    ::clearScreen();
                }
                break;
            }
            
            default:
                std::cout << "Invalid choice.\n";
        }
        
        if (enemy.isAlive()) {
            dmg = player.getHp();
            enemy.attack(&player);
            dmg -= player.getHp();
            std::cout << "Enemy dealt " << dmg << " damage!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::cout << "Press any key to continue...";
        getChar();
        ::clearScreen();
    }
    
    if (!player.isAlive()) {
        std::cout << "You died...\n";
    } else if (!enemy.isAlive()) {
        defeated = true;
    }
}

