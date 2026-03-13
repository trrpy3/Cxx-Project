#include "save_load.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

void saveGame(const Player& player, const std::string& locName, game_State state) {
    std::ofstream file("save.csv");
    if (!file.is_open())
        throw FileException("Cannot open save file for writing");
    file << "Player," << player.getHp() << "," << player.getLevel() << "," << player.getMoney() << ","
        << player.getExp() << "\n";
    file << "Location," << locName << "," << static_cast<int>(state) << "\n";
    file.close();
    std::cout << "Game saved.\n";
}
void loadGame(Player& player, std::string& locName, game_State& state) {
    std::ifstream file("save.csv");
    if (!file.is_open())
        throw FileException("Cannot open save file for reading");
    std::string line;
    std::getline(file, line);
    if (line.empty())
        throw GameException("Save file is corrupted");
    std::cout << "Load not fully implemented.\n";
}