#pragma once

#include "entity.h"
#include <memory>
#include "dialogue.h"

class NPC : public Entity {
public:
    NPC(int hp, int damage, int defense, int projectile_defense, int status, std::shared_ptr<Dialogue> dialogue);
    int getStatus() const;
    std::shared_ptr<Dialogue> getDialogue() const;
    std::string getTypeName() const override { return "NPC"; }
private:
    int status;
    std::shared_ptr<Dialogue> dialogue;
};
