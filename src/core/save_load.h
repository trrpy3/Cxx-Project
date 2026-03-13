#pragma once
#include "../entities/player.h"
#include "enums.h"
#include <string>
void saveGame(const Player& player, const std::string& locName, game_State state);
void loadGame(Player& player, std::string& locName, game_State& state);
