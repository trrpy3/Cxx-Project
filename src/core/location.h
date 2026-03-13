#pragma once

#include <string>
#include <vector>
#include <memory>
#include "enums.h"
#include "../entities/entity.h"

class Location {
public:
    Location(const std::string& name, location_Type type, unsigned int required_level);
    void addEntity(std::unique_ptr<Entity> entity);
    void addConnection(Location* location); 
    const std::vector<Location*>& getConnections() const;  
    const std::string& getName() const;
    location_Type getType() const;
    void enter(Player& player) {};
    unsigned int getRequiredLevel() const;
    std::vector<std::unique_ptr<Entity>>& getPool();

private:
    const std::string &name;
    location_Type type;
    unsigned int required_level;
    std::vector<std::unique_ptr<Entity>> pool;
    std::vector<Location*> connections;  
};