
#include "npc.h"
NPC::NPC(int hp, int damage, int defense, int projectile_defense, int status, std::shared_ptr<Dialogue> dialogue)
    : Entity(hp, damage, defense, projectile_defense), status(status), dialogue(std::move(dialogue)) {
}
int NPC::getStatus() const { return status; }
std::shared_ptr<Dialogue> NPC::getDialogue() const { return dialogue; }