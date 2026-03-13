#pragma once
#include "world.h"
#include "input.h"
#include "save_load.h"
#include "player.h"
#include <exception>
#include <iostream>
#include <iomanip>

class UI {
private:
    World& world;
    Player& player;

public:
    UI(World& w, Player& p) : world(w), player(p) {}

    void showLocationMenu() {
        clearScreen();
        Location* current = world.getCurrentLocation();
        
        std::cout << "+--------------------------------+\n";
        std::cout << "|     You are at: " << std::left << std::setw(12) << current->getName() << "|\n";
        std::cout << "+--------------------------------+\n";
        std::cout << "|  Where would you like to go?  |\n";
        std::cout << "+--------------------------------+\n";
        
        const auto& connections = current->getConnections();
        for (size_t i = 0; i < connections.size(); ++i) {
            std::cout << "|  " << (i + 1) << ". " << std::left << std::setw(22) 
                      << connections[i]->getName() << "|\n";
        }
        
        std::cout << "|  " << (connections.size() + 1) << ". Stay here            |\n";
        std::cout << "|  " << (connections.size() + 2) << ". Show inventory       |\n";
        std::cout << "|  " << (connections.size() + 3) << ". Show equipment       |\n";
        std::cout << "|  " << (connections.size() + 4) << ". Use item             |\n";
        std::cout << "|  " << (connections.size() + 5) << ". Save game            |\n";
        std::cout << "|  " << (connections.size() + 6) << ". Exit game            |\n";
        std::cout << "+--------------------------------+\n";
        std::cout << "Your HP: " << player.getHp() << "/" << Player::MAX_HP 
                  << " | Money: " << player.getMoney() << "\n";
        std::cout << "Choice: ";
    }

    void run() {
        bool running = true;
        while (running && player.isAlive()) {
            world.update();
            
            if (!player.isAlive()) break;
            
            showLocationMenu();
            
            int choice;
            std::cin >> choice;
            
            Location* current = world.getCurrentLocation();
            const auto& connections = current->getConnections();
            
            if (choice >= 1 && choice <= static_cast<int>(connections.size())) {
                world.moveTo(connections[choice - 1]);
            }
            else if (choice == static_cast<int>(connections.size() + 1)) {
                // Stay - do nothing
            }
            else if (choice == static_cast<int>(connections.size() + 2)) {
                player.showInventory();
                std::cout << "\nPress any key to continue...";
                getChar();
            }
            else if (choice == static_cast<int>(connections.size() + 3)) {
                player.showEquipment();
                std::cout << "\nPress any key to continue...";
                getChar();
            }
            else if (choice == static_cast<int>(connections.size() + 4)) {
                player.showInventory();
                std::cout << "Enter item index to use: ";
                int idx;
                std::cin >> idx;
                if (!player.useStuff(idx)) {
                    std::cout << "Invalid item.\n";
                }
                std::cout << "Press any key to continue...";
                getChar();
            }
            else if (choice == static_cast<int>(connections.size() + 5)) {
                try {
                    saveGame(player, current->getName(), game_State::safe);
                } catch (const std::exception& e) {
                    std::cerr << "Error saving game: " << e.what() << std::endl;
                }
                std::cout << "Press any key to continue...";
                getChar();
            }
            else if (choice == static_cast<int>(connections.size() + 6)) {
                running = false;
            }
            else {
                std::cout << "Invalid choice. Press any key to continue...";
                getChar();
            }
        }
    }
};