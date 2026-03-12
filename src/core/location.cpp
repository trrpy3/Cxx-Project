
#include "location.h"

Location::Location(const std::string& name, location_Type type, unsigned int required_level)
    : name(name), type(type), required_level(required_level) {
}

void Location::addEntity(std::unique_ptr<Entity> entity) {
    pool.push_back(std::move(entity));
}

const std::string& Location::getName() const { return name; }
location_Type Location::getType() const { return type; }
unsigned int Location::getRequiredLevel() const { return required_level; }
std::vector<std::unique_ptr<Entity>>& Location::getPool() { return pool; }