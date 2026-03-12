#pragma once

#include <string>
#include <vector>
#include <memory>
#include "enums.h"
#include "entity.h"

class Location {
public:
    Location(const std::string& name, location_Type type, unsigned int required_level);
    void addEntity(std::unique_ptr<Entity> entity);
    const std::string& getName() const;
    location_Type getType() const;
    unsigned int getRequiredLevel() const;
    std::vector<std::unique_ptr<Entity>>& getPool();

private:
    std::string name;
    location_Type type;
    unsigned int required_level;
    std::vector<std::unique_ptr<Entity>> pool;
};