#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "location.h"
#include "town.h"
#include "forest.h"
#include "swamp.h"
#include "mountain.h"
#include "cave.h"
#include "shop.h"
#include "../entities/player.h"
#include "../entities/enemy.h"

class World {
private:
    std::map<std::string, std::unique_ptr<Location>> locations;
    Location* currentLocation;
    Player* player;

public:
    World(Player* p) : currentLocation(nullptr), player(p) {}
    
    template<typename T, typename... Args>
    T* addLocation(const std::string& name, Args&&... args) {
        auto loc = std::make_unique<T>(name, std::forward<Args>(args)...);
        T* ptr = loc.get();
        locations[name] = std::move(loc);
        return ptr;
    }
    
    void connect(const std::string& from, const std::string& to, bool bidirectional = true) {
        auto* locFrom = locations[from].get();
        auto* locTo = locations[to].get();
        
        if (locFrom && locTo) {
            locFrom->addConnection(locTo);
            if (bidirectional) {
                locTo->addConnection(locFrom);
            }
        }
    }
    
    void setStartLocation(const std::string& name) {
        currentLocation = locations[name].get();
    }
    
    Location* getCurrentLocation() const { return currentLocation; }
    
    void moveTo(Location* newLoc) {
        if (newLoc) {
            currentLocation = newLoc;
        }
    }
    
    void update() {
        if (currentLocation && player) {
            currentLocation->enter(*player);
        }
    }
};