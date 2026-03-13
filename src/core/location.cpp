#include "location.h"
#include <iostream>

Location::Location(const std::string& name, location_Type type, unsigned int required_level)
    : name(name), type(type), required_level(required_level) {
}

void Location::addEntity(std::unique_ptr<Entity> entity) {
    pool.push_back(std::move(entity));
}

void Location::addConnection(Location* location) {
    connections.push_back(location);
}

const std::vector<Location*>& Location::getConnections() const {
    return connections;
}

void Location::enter(Player& player) {
    std::cout << "You are at " << name << ". Nothing special happens.\n";
}

const std::string& Location::getName() const { return name; }
location_Type Location::getType() const { return type; }
unsigned int Location::getRequiredLevel() const { return required_level; }
std::vector<std::unique_ptr<Entity>>& Location::getPool() { return pool; }